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
struct SiS_Private {scalar_t__ ChipType; int SiS_LCDInfo; } ;

/* Variables and functions */
 int LCDDualLink ; 
 scalar_t__ SIS_315H ; 
 scalar_t__ SiS_CRT2IsLCD (struct SiS_Private*) ; 
 scalar_t__ SiS_IsVAMode (struct SiS_Private*) ; 

__attribute__((used)) static bool
SiS_IsDualLink(struct SiS_Private *SiS_Pr)
{
#ifdef CONFIG_FB_SIS_315
   if(SiS_Pr->ChipType >= SIS_315H) {
      if((SiS_CRT2IsLCD(SiS_Pr)) ||
         (SiS_IsVAMode(SiS_Pr))) {
	 if(SiS_Pr->SiS_LCDInfo & LCDDualLink) return true;
      }
   }
#endif
   return false;
}