#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct SiS_Private {unsigned short SiS_CRT1Mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_ClearExt1Regs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_DisplayOn (struct SiS_Private*) ; 
 unsigned short SiS_GetRatePtr (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_LoadDAC (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_ResetSegmentRegisters (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetATTRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1CRTC (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1FIFO_310 (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1ModeRegs (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1Offset (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1Sync (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1VCLK (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRTCRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetGRCRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetMiscRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetSeqRegs (struct SiS_Private*,unsigned short) ; 

__attribute__((used)) static void
SiS_SetCRT1Group(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		 unsigned short ModeIdIndex)
{
	unsigned short StandTableIndex, rrti;

	SiS_Pr->SiS_CRT1Mode = ModeNo;

	if (ModeNo <= 0x13)
		StandTableIndex = 0;
	else
		StandTableIndex = 1;

	SiS_ResetSegmentRegisters(SiS_Pr);
	SiS_SetSeqRegs(SiS_Pr, StandTableIndex);
	SiS_SetMiscRegs(SiS_Pr, StandTableIndex);
	SiS_SetCRTCRegs(SiS_Pr, StandTableIndex);
	SiS_SetATTRegs(SiS_Pr, StandTableIndex);
	SiS_SetGRCRegs(SiS_Pr, StandTableIndex);
	SiS_ClearExt1Regs(SiS_Pr, ModeNo);

	rrti = SiS_GetRatePtr(SiS_Pr, ModeNo, ModeIdIndex);

	if (rrti != 0xFFFF) {
		SiS_SetCRT1Sync(SiS_Pr, rrti);
		SiS_SetCRT1CRTC(SiS_Pr, ModeNo, ModeIdIndex, rrti);
		SiS_SetCRT1Offset(SiS_Pr, ModeNo, ModeIdIndex, rrti);
		SiS_SetCRT1VCLK(SiS_Pr, ModeNo, rrti);
	}

	SiS_SetCRT1FIFO_310(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_SetCRT1ModeRegs(SiS_Pr, ModeNo, ModeIdIndex, rrti);

	SiS_LoadDAC(SiS_Pr, ModeNo, ModeIdIndex);

	SiS_DisplayOn(SiS_Pr);
}