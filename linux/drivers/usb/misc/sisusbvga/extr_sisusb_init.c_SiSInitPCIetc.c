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
 int /*<<< orphan*/  SiS_SetReg (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (struct SiS_Private*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void SiSInitPCIetc(struct SiS_Private *SiS_Pr)
{
	SiS_SetReg(SiS_Pr, SiS_Pr->SiS_P3c4, 0x20, 0xa1);
	/*  - Enable 2D (0x40)
	 *  - Enable 3D (0x02)
	 *  - Enable 3D vertex command fetch (0x10)
	 *  - Enable 3D command parser (0x08)
	 *  - Enable 3D G/L transformation engine (0x80)
	 */
	SiS_SetRegOR(SiS_Pr, SiS_Pr->SiS_P3c4, 0x1E, 0xDA);
}