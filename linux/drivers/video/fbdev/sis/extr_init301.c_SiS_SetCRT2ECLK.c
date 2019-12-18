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
struct SiS_Private {unsigned char* VirtualRomBase; int SiS_LCDInfo; scalar_t__ SiS_CustomT; int SiS_VBInfo; int /*<<< orphan*/  SiS_P3c4; scalar_t__ SiS_UseROM; TYPE_2__* SiS_VCLKData; int /*<<< orphan*/  SiS_SetFlag; TYPE_1__* SiS_RefIndex; } ;
struct TYPE_4__ {unsigned char SR2B; unsigned char SR2C; } ;
struct TYPE_3__ {int Ext_CRTVCLK; } ;

/* Variables and functions */
 scalar_t__ CUT_BARCO1024 ; 
 scalar_t__ CUT_BARCO1366 ; 
 int LCDPass11 ; 
 int /*<<< orphan*/  ProgrammingCRT2 ; 
 int SetCRT2ToLCDA ; 
 int SetInSlaveMode ; 
 unsigned short SiS_GetVCLK2Ptr (struct SiS_Private*,unsigned short,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,unsigned short,unsigned char) ; 

__attribute__((used)) static void
SiS_SetCRT2ECLK(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex,
           unsigned short RefreshRateTableIndex)
{
  unsigned char  *ROMAddr = SiS_Pr->VirtualRomBase;
  unsigned short clkbase, vclkindex = 0;
  unsigned char  sr2b, sr2c;

  if(SiS_Pr->SiS_LCDInfo & LCDPass11) {
     SiS_Pr->SiS_SetFlag &= (~ProgrammingCRT2);
     if(SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRTVCLK == 2) {
	RefreshRateTableIndex--;
     }
     vclkindex = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex,
                                    RefreshRateTableIndex);
     SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;
  } else {
     vclkindex = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex,
                                    RefreshRateTableIndex);
  }

  sr2b = SiS_Pr->SiS_VCLKData[vclkindex].SR2B;
  sr2c = SiS_Pr->SiS_VCLKData[vclkindex].SR2C;

  if((SiS_Pr->SiS_CustomT == CUT_BARCO1366) || (SiS_Pr->SiS_CustomT == CUT_BARCO1024)) {
     if(SiS_Pr->SiS_UseROM) {
	if(ROMAddr[0x220] & 0x01) {
	   sr2b = ROMAddr[0x227];
	   sr2c = ROMAddr[0x228];
	}
     }
  }

  clkbase = 0x02B;
  if(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) {
     if(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) {
	clkbase += 3;
     }
  }

  SiS_SetReg(SiS_Pr->SiS_P3c4,0x31,0x20);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase,sr2b);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase+1,sr2c);
  SiS_SetReg(SiS_Pr->SiS_P3c4,0x31,0x10);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase,sr2b);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase+1,sr2c);
  SiS_SetReg(SiS_Pr->SiS_P3c4,0x31,0x00);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase,sr2b);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase+1,sr2c);
}