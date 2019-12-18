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
struct SiS_Private {int SiS_DDC_DeviceAddr; } ;

/* Variables and functions */
 scalar_t__ SiS_SetStart (struct SiS_Private*) ; 
 scalar_t__ SiS_WriteDDC2Data (struct SiS_Private*,int) ; 

__attribute__((used)) static unsigned short
SiS_PrepareReadDDC(struct SiS_Private *SiS_Pr)
{
   if(SiS_SetStart(SiS_Pr)) return 0xFFFF;
   if(SiS_WriteDDC2Data(SiS_Pr, (SiS_Pr->SiS_DDC_DeviceAddr | 0x01))) {
      return 0xFFFF;
   }
   return 0;
}