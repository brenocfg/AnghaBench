#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {unsigned long SiS_P3c8; unsigned long SiS_P3c9; unsigned long SiS_P3c6; TYPE_2__* SiS_EModeIDTable; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_3__ {unsigned short St_ModeFlag; } ;

/* Variables and functions */
 unsigned short DACInfoFlag ; 
 unsigned char* SiS_CGA_DAC ; 
 unsigned char* SiS_EGA_DAC ; 
 unsigned char* SiS_MDA_DAC ; 
 int /*<<< orphan*/  SiS_SetRegByte (struct SiS_Private*,unsigned long,unsigned short) ; 
 unsigned char* SiS_VGA_DAC ; 
 int /*<<< orphan*/  SiS_WriteDAC (struct SiS_Private*,unsigned long,unsigned short,unsigned short,unsigned char const,unsigned char const,unsigned char const) ; 

__attribute__((used)) static void
SiS_LoadDAC(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
	    unsigned short mi)
{
	unsigned short data, data2, time, i, j, k, m, n, o;
	unsigned short si, di, bx, sf;
	unsigned long DACAddr, DACData;
	const unsigned char *table = NULL;

	if (ModeNo < 0x13)
		data = SiS_Pr->SiS_SModeIDTable[mi].St_ModeFlag;
	else
		data = SiS_Pr->SiS_EModeIDTable[mi].Ext_ModeFlag;

	data &= DACInfoFlag;

	j = time = 64;
	if (data == 0x00)
		table = SiS_MDA_DAC;
	else if (data == 0x08)
		table = SiS_CGA_DAC;
	else if (data == 0x10)
		table = SiS_EGA_DAC;
	else {
		j = 16;
		time = 256;
		table = SiS_VGA_DAC;
	}

	DACAddr = SiS_Pr->SiS_P3c8;
	DACData = SiS_Pr->SiS_P3c9;
	sf = 0;
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c6, 0xFF);

	SiS_SetRegByte(SiS_Pr, DACAddr, 0x00);

	for (i = 0; i < j; i++) {
		data = table[i];
		for (k = 0; k < 3; k++) {
			data2 = 0;
			if (data & 0x01)
				data2 += 0x2A;
			if (data & 0x02)
				data2 += 0x15;
			SiS_SetRegByte(SiS_Pr, DACData, (data2 << sf));
			data >>= 2;
		}
	}

	if (time == 256) {
		for (i = 16; i < 32; i++) {
			data = table[i] << sf;
			for (k = 0; k < 3; k++)
				SiS_SetRegByte(SiS_Pr, DACData, data);
		}
		si = 32;
		for (m = 0; m < 9; m++) {
			di = si;
			bx = si + 4;
			for (n = 0; n < 3; n++) {
				for (o = 0; o < 5; o++) {
					SiS_WriteDAC(SiS_Pr, DACData, sf, n,
						     table[di], table[bx],
						     table[si]);
					si++;
				}
				si -= 2;
				for (o = 0; o < 3; o++) {
					SiS_WriteDAC(SiS_Pr, DACData, sf, n,
						     table[di], table[si],
						     table[bx]);
					si--;
				}
			}
			si += 5;
		}
	}
}