#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msm_gpu {int /*<<< orphan*/  icc_path; } ;
struct TYPE_2__ {struct msm_gpu base; } ;
struct a6xx_gmu {int /*<<< orphan*/  dev; int /*<<< orphan*/  clocks; int /*<<< orphan*/  nr_clocks; int /*<<< orphan*/  gxpd; scalar_t__ hung; } ;
struct a6xx_gpu {TYPE_1__ base; struct a6xx_gmu gmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_gmu_force_off (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_gmu_shutdown (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icc_set_bw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

int a6xx_gmu_stop(struct a6xx_gpu *a6xx_gpu)
{
	struct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	struct msm_gpu *gpu = &a6xx_gpu->base.base;

	if (!pm_runtime_active(gmu->dev))
		return 0;

	/*
	 * Force the GMU off if we detected a hang, otherwise try to shut it
	 * down gracefully
	 */
	if (gmu->hung)
		a6xx_gmu_force_off(gmu);
	else
		a6xx_gmu_shutdown(gmu);

	/* Remove the bus vote */
	icc_set_bw(gpu->icc_path, 0, 0);

	/*
	 * Make sure the GX domain is off before turning off the GMU (CX)
	 * domain. Usually the GMU does this but only if the shutdown sequence
	 * was successful
	 */
	if (!IS_ERR_OR_NULL(gmu->gxpd))
		pm_runtime_put_sync(gmu->gxpd);

	clk_bulk_disable_unprepare(gmu->nr_clocks, gmu->clocks);

	pm_runtime_put_sync(gmu->dev);

	return 0;
}