#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"KPD_interface.h"
#include"CLCD_interface.h"
#include"util/delay.h"
int clcnum(u32 ch);
u32 aton(u32 num[], u8 s);
int main(void) {
	u32 x1[10],x2[10], op, c = 0, value, s;
	//lcd
	DIO_u8SetPortDir(DIO_PORTD, DIO_PORT_OUT);
	DIO_u8SetPortDir(DIO_PORTC, 0b00000111);
	//kpd
	DIO_u8SetPortDir(DIO_PORTA, 0b00001111);
	DIO_u8SetPortValue(DIO_PORTA, 0xff);
	CLCD_voidInit();
	u8 i = 0, j = 0, n1, n2;

	while (1) {
		do {
			value = KPD_u8GetPressedKey();
		} while (value == 0xff);
		u32  z = 0, q = 0;
		if (c == 0 && value != 4 && value != 8 && value != 12 && value != 16
				&& value != 15) {
			z = clcnum(value);
			x1[i] = z;
			i++;
			// CLCD_voidSendData(x1[i]+'0');
			CLCD_voidWriteNumber(z);
			// c++;
		} else if (value == 4 || value == 8 || value == 12 || value == 16) {
			n1 = aton(x1, i);
			//CLCD_voidWriteNumber(n1);
			op = value;
			switch (op) {
			case 4:
				CLCD_voidSendData('/');
				break;
			case 8:
				CLCD_voidSendData('*');
				break;
			case 12:
				CLCD_voidSendData('-');
				break;
			case 16:
				CLCD_voidSendData('+');
				break;
			}
			c++;
		} else if (c == 1 && value != 15) {
			q = clcnum(value);
			x2[j] = q;
			j++;
			CLCD_voidWriteNumber(q);
			//c++;
		}
		if (value == 15) {

			n2 = aton(x2, j);
			CLCD_voidSendData('=');
			switch (op) {
			case 4:
				s = n1 / n2;
				CLCD_voidWriteNumber(s);
				break;
			case 8:
				s = n1 * n2;
				CLCD_voidWriteNumber(s);
				break;
			case 12:
				s = n1 - n2;
				CLCD_voidWriteNumber(s);
				break;
			case 16:
				s = n1 + n2;
				CLCD_voidWriteNumber(s);
				break;
			}
		}

		if (value == 13) {
			n1=0;
			n2=0;
			q=0;
			z=0;
			x1[10]=0;
			x2[10]=0;
			c = 0;
			s=0;
			i=0;
			j=0;
			CLCD_voidSendCommand(0x01);
		}
	}

}

int clcnum(u32 ch) {
	u8 num;
	if (ch == 1) {
		num = 7;
	} else if (ch == 2) {
		num = 8;
	} else if (ch == 3) {
		num = 9;
	} else if (ch == 5) {
		num = 4;
	} else if (ch == 6) {
		num = 5;
	} else if (ch == 7) {
		num = 6;
	} else if (ch == 9) {
		num = 1;
	} else if (ch == 10) {
		num = 2;
	} else if (ch == 11) {
		num = 3;
	} else if (ch == 14) {
		num = 0;
	}
	return num;
}
u32 aton(u32 num[], u8 s) {
	u8 i;
	u32 temp1 = 0;
	for (i = 0; i < s; i++) {

		temp1 = temp1 * 10 + num[i];
	}
	return temp1;
}
