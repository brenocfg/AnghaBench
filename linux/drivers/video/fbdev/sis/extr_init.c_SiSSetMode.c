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
struct SiS_Private {int UseCustomMode; int CRT1UsesCustomMode; int SiS_flag_clearbuffer; int SiS_VGAINFO; int SiS_VBType; scalar_t__ ChipType; int SiS_VBInfo; int SiS_IF_DEF_LVDS; scalar_t__ SiS_IF_DEF_CH70xx; scalar_t__ SiS_IF_DEF_TRUMPION; int /*<<< orphan*/  SiS_P3c4; int /*<<< orphan*/  SiS_P3d4; int /*<<< orphan*/  SiS_ROMNew; int /*<<< orphan*/  SiS_Part1Port; int /*<<< orphan*/  SiS_P3c6; int /*<<< orphan*/  CModeFlag; int /*<<< orphan*/  CModeFlag_CRT1; int /*<<< orphan*/  CSRClock; int /*<<< orphan*/  CSRClock_CRT1; int /*<<< orphan*/  SiS_Part2Port; int /*<<< orphan*/  IOAddress; } ;
typedef  int /*<<< orphan*/  SISIOADDRESS ;

/* Variables and functions */
 scalar_t__ IS_SIS650 ; 
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_630 ; 
 scalar_t__ SIS_730 ; 
 int SetCRT2ToLCD ; 
 int SetCRT2ToLCDA ; 
 int SetSimuScanMode ; 
 int /*<<< orphan*/  SiSDetermineROMUsage (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiSInitPCIetc (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiSInitPtr (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiSRegInit (struct SiS_Private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiSSetLVDSetc (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_CheckMemorySize (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_CloseCRTC (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_DisplayOn (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_GetLCDResInfo (struct SiS_Private*,unsigned short,unsigned short) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_GetSysFlags (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_GetVBInfo (struct SiS_Private*,unsigned short,unsigned short,int) ; 
 int /*<<< orphan*/  SiS_GetVBType (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_Handle760 (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_HandleCRT1 (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_InitVB (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_IsDualEdge (struct SiS_Private*) ; 
 scalar_t__ SiS_IsVAMode (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_OpenCRTC (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_ResetVB (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SearchModeID (struct SiS_Private*,unsigned short*,unsigned short*) ; 
 int /*<<< orphan*/  SiS_SetCRT1Group (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetCRT2Group (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetLowModeTest (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetTVMode (struct SiS_Private*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetYPbPr (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_StrangeStuff (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_UnLockCRT2 (struct SiS_Private*) ; 
 int SwitchCRT2 ; 
 int VB_SIS30xBLV ; 
 int VB_SISVB ; 

bool
SiSSetMode(struct SiS_Private *SiS_Pr, unsigned short ModeNo)
{
   SISIOADDRESS BaseAddr = SiS_Pr->IOAddress;
   unsigned short RealModeNo, ModeIdIndex;
   unsigned char  backupreg = 0;
   unsigned short KeepLockReg;

   SiS_Pr->UseCustomMode = false;
   SiS_Pr->CRT1UsesCustomMode = false;

   SiS_Pr->SiS_flag_clearbuffer = 0;

   if(SiS_Pr->UseCustomMode) {
      ModeNo = 0xfe;
   } else {
      if(!(ModeNo & 0x80)) SiS_Pr->SiS_flag_clearbuffer = 1;
      ModeNo &= 0x7f;
   }

   /* Don't use FSTN mode for CRT1 */
   RealModeNo = ModeNo;
   if(ModeNo == 0x5b) ModeNo = 0x56;

   SiSInitPtr(SiS_Pr);
   SiSRegInit(SiS_Pr, BaseAddr);
   SiS_GetSysFlags(SiS_Pr);

   SiS_Pr->SiS_VGAINFO = 0x11;

   KeepLockReg = SiS_GetReg(SiS_Pr->SiS_P3c4,0x05);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x05,0x86);

   SiSInitPCIetc(SiS_Pr);
   SiSSetLVDSetc(SiS_Pr);
   SiSDetermineROMUsage(SiS_Pr);

   SiS_UnLockCRT2(SiS_Pr);

   if(!SiS_Pr->UseCustomMode) {
      if(!(SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex))) return false;
   } else {
      ModeIdIndex = 0;
   }

   SiS_GetVBType(SiS_Pr);

   /* Init/restore some VB registers */
   SiS_InitVB(SiS_Pr);
   if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {
      if(SiS_Pr->ChipType >= SIS_315H) {
         SiS_ResetVB(SiS_Pr);
	 SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x32,0x10);
	 SiS_SetRegOR(SiS_Pr->SiS_Part2Port,0x00,0x0c);
         backupreg = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
      } else {
         backupreg = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35);
      }
   }

   /* Get VB information (connectors, connected devices) */
   SiS_GetVBInfo(SiS_Pr, ModeNo, ModeIdIndex, (SiS_Pr->UseCustomMode) ? 0 : 1);
   SiS_SetYPbPr(SiS_Pr);
   SiS_SetTVMode(SiS_Pr, ModeNo, ModeIdIndex);
   SiS_GetLCDResInfo(SiS_Pr, ModeNo, ModeIdIndex);
   SiS_SetLowModeTest(SiS_Pr, ModeNo);

   /* Check memory size (kernel framebuffer driver only) */
   if(!SiS_CheckMemorySize(SiS_Pr, ModeNo, ModeIdIndex)) {
      return false;
   }

   SiS_OpenCRTC(SiS_Pr);

   if(SiS_Pr->UseCustomMode) {
      SiS_Pr->CRT1UsesCustomMode = true;
      SiS_Pr->CSRClock_CRT1 = SiS_Pr->CSRClock;
      SiS_Pr->CModeFlag_CRT1 = SiS_Pr->CModeFlag;
   } else {
      SiS_Pr->CRT1UsesCustomMode = false;
   }

   /* Set mode on CRT1 */
   if( (SiS_Pr->SiS_VBInfo & (SetSimuScanMode | SetCRT2ToLCDA)) ||
       (!(SiS_Pr->SiS_VBInfo & SwitchCRT2)) ) {
      SiS_SetCRT1Group(SiS_Pr, ModeNo, ModeIdIndex);
   }

   /* Set mode on CRT2 */
   if(SiS_Pr->SiS_VBInfo & (SetSimuScanMode | SwitchCRT2 | SetCRT2ToLCDA)) {
      if( (SiS_Pr->SiS_VBType & VB_SISVB)    ||
	  (SiS_Pr->SiS_IF_DEF_LVDS     == 1) ||
	  (SiS_Pr->SiS_IF_DEF_CH70xx   != 0) ||
	  (SiS_Pr->SiS_IF_DEF_TRUMPION != 0) ) {
	 SiS_SetCRT2Group(SiS_Pr, RealModeNo);
      }
   }

   SiS_HandleCRT1(SiS_Pr);

   SiS_StrangeStuff(SiS_Pr);

   SiS_DisplayOn(SiS_Pr);
   SiS_SetRegByte(SiS_Pr->SiS_P3c6,0xFF);

#ifdef CONFIG_FB_SIS_315
   if(SiS_Pr->ChipType >= SIS_315H) {
      if(SiS_Pr->SiS_IF_DEF_LVDS == 1) {
	 if(!(SiS_IsDualEdge(SiS_Pr))) {
	    SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xfb);
	 }
      }
   }
#endif

   if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {
      if(SiS_Pr->ChipType >= SIS_315H) {
#ifdef CONFIG_FB_SIS_315
	 if(!SiS_Pr->SiS_ROMNew) {
	    if(SiS_IsVAMode(SiS_Pr)) {
	       SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x35,0x01);
	    } else {
	       SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x35,0xFE);
	    }
	 }

	 SiS_SetReg(SiS_Pr->SiS_P3d4,0x38,backupreg);

	 if((IS_SIS650) && (SiS_GetReg(SiS_Pr->SiS_P3d4,0x30) & 0xfc)) {
	    if((ModeNo == 0x03) || (ModeNo == 0x10)) {
	       SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x51,0x80);
	       SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x56,0x08);
	    }
	 }

	 if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x30) & SetCRT2ToLCD) {
	    SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x38,0xfc);
	 }
#endif
      } else if((SiS_Pr->ChipType == SIS_630) ||
	        (SiS_Pr->ChipType == SIS_730)) {
	 SiS_SetReg(SiS_Pr->SiS_P3d4,0x35,backupreg);
      }
   }

   SiS_CloseCRTC(SiS_Pr);

   SiS_Handle760(SiS_Pr);

   /* We never lock registers in XF86 */
   if(KeepLockReg != 0xA1) SiS_SetReg(SiS_Pr->SiS_P3c4,0x05,0x00);

   return true;
}