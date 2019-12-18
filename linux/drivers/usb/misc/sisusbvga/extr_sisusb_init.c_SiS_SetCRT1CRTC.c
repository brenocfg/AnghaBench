#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {scalar_t__ SiS_ModeType; int /*<<< orphan*/  SiS_P3d4; TYPE_3__* SiS_CRT1Table; int /*<<< orphan*/  SiS_P3c4; TYPE_2__* SiS_RefIndex; TYPE_1__* SiS_EModeIDTable; } ;
struct TYPE_6__ {int* CR; } ;
struct TYPE_5__ {unsigned char Ext_CRT1CRTC; } ;
struct TYPE_4__ {unsigned short Ext_ModeFlag; } ;

/* Variables and functions */
 unsigned short DoubleScanMode ; 
 scalar_t__ ModeVGA ; 
 int /*<<< orphan*/  SiS_SetReg (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (struct SiS_Private*,int /*<<< orphan*/ ,int,int,unsigned short) ; 

__attribute__((used)) static void
SiS_SetCRT1CRTC(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex, unsigned short rrti)
{
	unsigned char index;
	unsigned short temp, i, j, modeflag;

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3d4, 0x11, 0x7f);

	modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

	index = SiS_Pr->SiS_RefIndex[rrti].Ext_CRT1CRTC;

	for (i = 0, j = 0; i <= 7; i++, j++) {
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, j,
			   SiS_Pr->SiS_CRT1Table[index].CR[i]);
	}
	for (j = 0x10; i <= 10; i++, j++) {
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, j,
			   SiS_Pr->SiS_CRT1Table[index].CR[i]);
	}
	for (j = 0x15; i <= 12; i++, j++) {
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, j,
			   SiS_Pr->SiS_CRT1Table[index].CR[i]);
	}
	for (j = 0x0A; i <= 15; i++, j++) {
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, j,
			   SiS_Pr->SiS_CRT1Table[index].CR[i]);
	}

	temp = SiS_Pr->SiS_CRT1Table[index].CR[16] & 0xE0;
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0E, temp);

	temp = ((SiS_Pr->SiS_CRT1Table[index].CR[16]) & 0x01) << 5;
	if (modeflag & DoubleScanMode)
		temp |= 0x80;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3d4, 0x09, 0x5F, temp);

	if (SiS_Pr->SiS_ModeType > ModeVGA)
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x14, 0x4F);
}