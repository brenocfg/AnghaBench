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
struct SiS_Private {int /*<<< orphan*/  SiS_Part4Port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_DDC2Delay (struct SiS_Private*,int) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 

void
SiS_SiS30xBLOff(struct SiS_Private *SiS_Pr)
{
  /* Switch off LCD backlight on SiS30xLV */
  SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xFE);
  SiS_DDC2Delay(SiS_Pr,0xff00);
}