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
struct SiS_Private {int SiS_VBInfo; scalar_t__ ChipType; int SiS_LCDTypeInfo; scalar_t__ SiS_CustomT; int SiS_LCDInfo; struct SiS_LVDSDes* SiS_PanelType04_2b; struct SiS_LVDSDes* SiS_PanelType04_1b; struct SiS_LVDSDes* SiS_PanelType04_2a; struct SiS_LVDSDes* SiS_PanelType04_1a; } ;
struct SiS_LVDSDes {int dummy; } ;

/* Variables and functions */
 scalar_t__ CUT_BARCO1024 ; 
 scalar_t__ CUT_BARCO1366 ; 
 int DontExpandLCD ; 
 scalar_t__ SIS_315H ; 
 int SetCRT2ToLCD ; 

__attribute__((used)) static const struct SiS_LVDSDes *
SiS_GetLVDSDesPtr(struct SiS_Private *SiS_Pr)
{
   const struct SiS_LVDSDes *PanelDesPtr = NULL;

#ifdef CONFIG_FB_SIS_300
   if(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) {

      if(SiS_Pr->ChipType < SIS_315H) {
	 if(SiS_Pr->SiS_LCDTypeInfo == 4) {
	    if(SiS_Pr->SiS_CustomT == CUT_BARCO1366) {
	       PanelDesPtr = SiS_Pr->SiS_PanelType04_1a;
	       if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
		  PanelDesPtr = SiS_Pr->SiS_PanelType04_2a;
	       }
            } else if(SiS_Pr->SiS_CustomT == CUT_BARCO1024) {
	       PanelDesPtr = SiS_Pr->SiS_PanelType04_1b;
	       if(SiS_Pr->SiS_LCDInfo & DontExpandLCD) {
		  PanelDesPtr = SiS_Pr->SiS_PanelType04_2b;
	       }
	    }
	 }
      }
   }
#endif
   return PanelDesPtr;
}