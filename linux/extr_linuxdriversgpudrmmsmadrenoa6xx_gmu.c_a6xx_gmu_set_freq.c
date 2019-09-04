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
struct a6xx_gmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMU_OOB_DCVS_SET ; 
 int /*<<< orphan*/  REG_A6XX_GMU_DCVS_ACK_OPTION ; 
 int /*<<< orphan*/  REG_A6XX_GMU_DCVS_BW_SETTING ; 
 int /*<<< orphan*/  REG_A6XX_GMU_DCVS_PERF_SETTING ; 
 int /*<<< orphan*/  REG_A6XX_GMU_DCVS_RETURN ; 
 int /*<<< orphan*/  a6xx_gmu_clear_oob (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_gmu_set_oob (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int a6xx_gmu_set_freq(struct a6xx_gmu *gmu, int index)
{
	gmu_write(gmu, REG_A6XX_GMU_DCVS_ACK_OPTION, 0);

	gmu_write(gmu, REG_A6XX_GMU_DCVS_PERF_SETTING,
		((index << 24) & 0xff) | (3 & 0xf));

	/*
	 * Send an invalid index as a vote for the bus bandwidth and let the
	 * firmware decide on the right vote
	 */
	gmu_write(gmu, REG_A6XX_GMU_DCVS_BW_SETTING, 0xff);

	/* Set and clear the OOB for DCVS to trigger the GMU */
	a6xx_gmu_set_oob(gmu, GMU_OOB_DCVS_SET);
	a6xx_gmu_clear_oob(gmu, GMU_OOB_DCVS_SET);

	return gmu_read(gmu, REG_A6XX_GMU_DCVS_RETURN);
}