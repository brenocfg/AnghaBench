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
typedef  int u32 ;
struct a6xx_gmu {int* gx_arc_votes; int nr_gpu_freqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMU_OOB_BOOT_SLUMBER ; 
 int /*<<< orphan*/  REG_A6XX_GMU_BOOT_SLUMBER_OPTION ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GX_VOTE_IDX ; 
 int /*<<< orphan*/  REG_A6XX_GMU_MX_VOTE_IDX ; 
 int a6xx_gmu_set_oob (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int a6xx_gmu_gfx_rail_on(struct a6xx_gmu *gmu)
{
	u32 vote;

	/* Let the GMU know we are getting ready for boot */
	gmu_write(gmu, REG_A6XX_GMU_BOOT_SLUMBER_OPTION, 0);

	/* Choose the "default" power level as the highest available */
	vote = gmu->gx_arc_votes[gmu->nr_gpu_freqs - 1];

	gmu_write(gmu, REG_A6XX_GMU_GX_VOTE_IDX, vote & 0xff);
	gmu_write(gmu, REG_A6XX_GMU_MX_VOTE_IDX, (vote >> 8) & 0xff);

	/* Let the GMU know the boot sequence has started */
	return a6xx_gmu_set_oob(gmu, GMU_OOB_BOOT_SLUMBER);
}