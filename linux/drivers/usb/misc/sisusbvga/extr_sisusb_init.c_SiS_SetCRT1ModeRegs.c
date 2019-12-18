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
struct SiS_Private {scalar_t__ SiS_ModeType; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_P3c4; TYPE_3__* SiS_RefIndex; TYPE_2__* SiS_EModeIDTable; TYPE_1__* SiS_SModeIDTable; } ;
struct TYPE_6__ {unsigned short Ext_InfoFlag; } ;
struct TYPE_5__ {unsigned short Ext_ModeFlag; } ;
struct TYPE_4__ {unsigned short St_ModeFlag; } ;

/* Variables and functions */
 unsigned short HalfDCLK ; 
 unsigned short InterlaceMode ; 
 unsigned short LineCompareOff ; 
 scalar_t__ ModeEGA ; 
 scalar_t__ ModeText ; 
 int ModeVGA ; 
 int SiS_GetReg (struct SiS_Private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetReg (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegANDOR (struct SiS_Private*,int /*<<< orphan*/ ,int,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegOR (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetVCLKState (struct SiS_Private*,unsigned short,unsigned short) ; 

__attribute__((used)) static void
SiS_SetCRT1ModeRegs(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		    unsigned short ModeIdIndex, unsigned short rrti)
{
	unsigned short data, infoflag = 0, modeflag;

	if (ModeNo <= 0x13)
		modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
	else {
		modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
		infoflag = SiS_Pr->SiS_RefIndex[rrti].Ext_InfoFlag;
	}

	/* Disable DPMS */
	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x1F, 0x3F);

	data = 0;
	if (ModeNo > 0x13) {
		if (SiS_Pr->SiS_ModeType > ModeEGA) {
			data |= 0x02;
			data |= ((SiS_Pr->SiS_ModeType - ModeVGA) << 2);
		}
		if (infoflag & InterlaceMode)
			data |= 0x20;
	}
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x06, 0xC0, data);

	data = 0;
	if (infoflag & InterlaceMode) {
		/* data = (Hsync / 8) - ((Htotal / 8) / 2) + 3 */
		unsigned short hrs =
		    (SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x04) |
		     ((SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0b) & 0xc0) << 2))
		    - 3;
		unsigned short hto =
		    (SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x00) |
		     ((SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0b) & 0x03) << 8))
		    + 5;
		data = hrs - (hto >> 1) + 3;
	}
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x19, (data & 0xFF));
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3d4, 0x1a, 0xFC, (data >> 8));

	if (modeflag & HalfDCLK)
		SiS_SetRegOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x01, 0x08);

	data = 0;
	if (modeflag & LineCompareOff)
		data = 0x08;
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0F, 0xB7, data);

	if ((SiS_Pr->SiS_ModeType == ModeEGA) && (ModeNo > 0x13))
		SiS_SetRegOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x0F, 0x40);

	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3c4, 0x31, 0xfb);

	data = 0x60;
	if (SiS_Pr->SiS_ModeType != ModeText) {
		data ^= 0x60;
		if (SiS_Pr->SiS_ModeType != ModeEGA)
			data ^= 0xA0;
	}
	SiS_SetRegANDOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x21, 0x1F, data);

	SiS_SetVCLKState(SiS_Pr, ModeNo, rrti);

	if (SiS_GetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x31) & 0x40)
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x52, 0x2c);
	else
		SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x52, 0x6c);
}