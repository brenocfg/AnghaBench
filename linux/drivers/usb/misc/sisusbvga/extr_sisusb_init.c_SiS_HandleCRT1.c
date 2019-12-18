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
struct SiS_Private {int /*<<< orphan*/  SiS_MyCR63; int /*<<< orphan*/  SiS_P3d4; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetRegAND (struct SiS_Private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SiS_HandleCRT1(struct SiS_Private *SiS_Pr)
{
	/* Enable CRT1 gating */
	SiS_SetRegAND(SiS_Pr, SiS_Pr->SiS_P3d4, SiS_Pr->SiS_MyCR63, 0xbf);
}