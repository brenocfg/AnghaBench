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
struct SiS_Private {int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetSegmentReg (struct SiS_Private*,unsigned short) ; 

__attribute__((used)) static void
SiS_SetSegmentRegOver(struct SiS_Private *SiS_Pr, unsigned short value)
{
   unsigned short temp = value >> 8;

   temp &= 0x07;
   temp |= (temp << 4);
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x1d,temp);
   SiS_SetSegmentReg(SiS_Pr, value);
}