#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct SiS_Private {unsigned long IOAddress; int SiS_ModeType; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_P3c6; int /*<<< orphan*/  SiS_SetFlag; TYPE_1__* SiS_EModeIDTable; int /*<<< orphan*/  SiS_P3c4; } ;
struct TYPE_2__ {int Ext_ModeFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  LowModeTests ; 
 int ModeTypeMask ; 
 int /*<<< orphan*/  SiSInitPCIetc (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiSUSBRegInit (struct SiS_Private*,unsigned long) ; 
 int /*<<< orphan*/  SiSUSB_InitPtr (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_DisplayOn (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_GetSysFlags (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_HandleCRT1 (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SearchModeID (struct SiS_Private*,unsigned short*,unsigned short*) ; 
 int /*<<< orphan*/  SiS_SetCRT1Group (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (struct SiS_Private*,int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegByte (struct SiS_Private*,int /*<<< orphan*/ ,int) ; 

int SiSUSBSetMode(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
	unsigned short ModeIdIndex;
	unsigned long BaseAddr = SiS_Pr->IOAddress;

	SiSUSB_InitPtr(SiS_Pr);
	SiSUSBRegInit(SiS_Pr, BaseAddr);
	SiS_GetSysFlags(SiS_Pr);

	if (!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex)))
		return 0;

	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x05, 0x86);

	SiSInitPCIetc(SiS_Pr);

	ModeNo &= 0x7f;

	SiS_Pr->SiS_ModeType =
	    SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag & ModeTypeMask;

	SiS_Pr->SiS_SetFlag = LowModeTests;

	/* Set mode on CRT1 */
	SiS_SetCRT1Group(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_HandleCRT1(SiS_Pr);

	SiS_DisplayOn(SiS_Pr);
	SiS_SetRegByte(SiS_Pr, SiS_Pr->SiS_P3c6, 0xFF);

	/* Store mode number */
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3d4, 0x34, ModeNo);

	return 1;
}