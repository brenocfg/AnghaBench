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
struct SiS_Private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetSegRegLower (struct SiS_Private*,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetSegRegUpper (struct SiS_Private*,unsigned short) ; 

__attribute__((used)) static void SiS_SetSegmentReg(struct SiS_Private *SiS_Pr, unsigned short value)
{
	SiS_SetSegRegLower(SiS_Pr, value);
	SiS_SetSegRegUpper(SiS_Pr, value);
}