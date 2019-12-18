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
struct SiS_Private {unsigned short SiS_CRT1Mode; int SiS_SetFlag; int SiS_VBInfo; int ChipType; scalar_t__ SiS_flag_clearbuffer; int /*<<< orphan*/  SiS_P3cc; int /*<<< orphan*/  SiS_P3c2; int /*<<< orphan*/  SiS_P3c4; scalar_t__ SiS_SelectCRT2Rate; } ;

/* Variables and functions */
 int LowModeTests ; 
 int ProgrammingCRT2 ; 
#define  SIS_300 131 
#define  SIS_540 130 
#define  SIS_630 129 
#define  SIS_730 128 
 int SetCRT2ToLCDA ; 
 int SetInSlaveMode ; 
 int SetSimuScanMode ; 
 int /*<<< orphan*/  SiS_ClearBuffer (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_ClearExt1Regs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_DisableBridge (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_DisplayOn (struct SiS_Private*) ; 
 unsigned short SiS_GetModePtr (struct SiS_Private*,unsigned short,unsigned short) ; 
 unsigned short SiS_GetRatePtr (struct SiS_Private*,unsigned short,unsigned short) ; 
 int SiS_GetRegByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_LoadDAC (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_ResetCRT1VCLK (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_ResetSegmentRegisters (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetATTRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1CRTC (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1FIFO_300 (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1FIFO_310 (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1FIFO_630 (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1ModeRegs (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1Offset (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1Sync (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT1VCLK (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRTCRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetGRCRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetMiscRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned char) ; 
 int /*<<< orphan*/  SiS_SetRegByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetSeqRegs (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetupDualChip (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_WaitRetrace1 (struct SiS_Private*) ; 
 int SwitchCRT2 ; 
 int XGI_20 ; 
 int XGI_40 ; 

__attribute__((used)) static void
SiS_SetCRT1Group(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
   unsigned short StandTableIndex, RefreshRateTableIndex;

   SiS_Pr->SiS_CRT1Mode = ModeNo;

   StandTableIndex = SiS_GetModePtr(SiS_Pr, ModeNo, ModeIdIndex);

   if(SiS_Pr->SiS_SetFlag & LowModeTests) {
      if(SiS_Pr->SiS_VBInfo & (SetSimuScanMode | SwitchCRT2)) {
         SiS_DisableBridge(SiS_Pr);
      }
   }

   SiS_ResetSegmentRegisters(SiS_Pr);

   SiS_SetSeqRegs(SiS_Pr, StandTableIndex);
   SiS_SetMiscRegs(SiS_Pr, StandTableIndex);
   SiS_SetCRTCRegs(SiS_Pr, StandTableIndex);
   SiS_SetATTRegs(SiS_Pr, StandTableIndex);
   SiS_SetGRCRegs(SiS_Pr, StandTableIndex);
   SiS_ClearExt1Regs(SiS_Pr, ModeNo);
   SiS_ResetCRT1VCLK(SiS_Pr);

   SiS_Pr->SiS_SelectCRT2Rate = 0;
   SiS_Pr->SiS_SetFlag &= (~ProgrammingCRT2);

   if(SiS_Pr->SiS_VBInfo & SetSimuScanMode) {
      if(SiS_Pr->SiS_VBInfo & SetInSlaveMode) {
         SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;
      }
   }

   if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) {
      SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;
   }

   RefreshRateTableIndex = SiS_GetRatePtr(SiS_Pr, ModeNo, ModeIdIndex);

   if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
      SiS_Pr->SiS_SetFlag &= ~ProgrammingCRT2;
   }

   if(RefreshRateTableIndex != 0xFFFF) {
      SiS_SetCRT1Sync(SiS_Pr, RefreshRateTableIndex);
      SiS_SetCRT1CRTC(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      SiS_SetCRT1Offset(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      SiS_SetCRT1VCLK(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
   }

   switch(SiS_Pr->ChipType) {
#ifdef CONFIG_FB_SIS_300
   case SIS_300:
      SiS_SetCRT1FIFO_300(SiS_Pr, ModeNo, RefreshRateTableIndex);
      break;
   case SIS_540:
   case SIS_630:
   case SIS_730:
      SiS_SetCRT1FIFO_630(SiS_Pr, ModeNo, RefreshRateTableIndex);
      break;
#endif
   default:
#ifdef CONFIG_FB_SIS_315
      if(SiS_Pr->ChipType == XGI_20) {
         unsigned char sr2b = 0, sr2c = 0;
         switch(ModeNo) {
	 case 0x00:
	 case 0x01: sr2b = 0x4e; sr2c = 0xe9; break;
	 case 0x04:
	 case 0x05:
	 case 0x0d: sr2b = 0x1b; sr2c = 0xe3; break;
	 }
	 if(sr2b) {
            SiS_SetReg(SiS_Pr->SiS_P3c4,0x2b,sr2b);
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x2c,sr2c);
	    SiS_SetRegByte(SiS_Pr->SiS_P3c2,(SiS_GetRegByte(SiS_Pr->SiS_P3cc) | 0x0c));
	 }
      }
      SiS_SetCRT1FIFO_310(SiS_Pr, ModeNo, ModeIdIndex);
#endif
      break;
   }

   SiS_SetCRT1ModeRegs(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);

#ifdef CONFIG_FB_SIS_315
   if(SiS_Pr->ChipType == XGI_40) {
      SiS_SetupDualChip(SiS_Pr);
   }
#endif

   SiS_LoadDAC(SiS_Pr, ModeNo, ModeIdIndex);

   if(SiS_Pr->SiS_flag_clearbuffer) {
      SiS_ClearBuffer(SiS_Pr, ModeNo);
   }

   if(!(SiS_Pr->SiS_VBInfo & (SetSimuScanMode | SwitchCRT2 | SetCRT2ToLCDA))) {
      SiS_WaitRetrace1(SiS_Pr);
      SiS_DisplayOn(SiS_Pr);
   }
}