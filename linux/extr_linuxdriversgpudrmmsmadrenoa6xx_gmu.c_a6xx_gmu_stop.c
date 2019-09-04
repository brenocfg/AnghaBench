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
struct a6xx_gmu {int /*<<< orphan*/  dev; int /*<<< orphan*/  clocks; int /*<<< orphan*/  nr_clocks; } ;
struct a6xx_gpu {struct a6xx_gmu gmu; } ;

/* Variables and functions */
 int A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS_GPUBUSYIGNAHB ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS2 ; 
 int /*<<< orphan*/  REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE ; 
 int /*<<< orphan*/  a6xx_gmu_irq_disable (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_gmu_notify_slumber (struct a6xx_gmu*) ; 
 int a6xx_gmu_wait_for_idle (struct a6xx_gpu*) ; 
 int /*<<< orphan*/  a6xx_hfi_stop (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_rpmh_stop (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int gmu_poll_timeout (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

int a6xx_gmu_stop(struct a6xx_gpu *a6xx_gpu)
{
	struct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	u32 val;

	/*
	 * The GMU may still be in slumber unless the GPU started so check and
	 * skip putting it back into slumber if so
	 */
	val = gmu_read(gmu, REG_A6XX_GPU_GMU_CX_GMU_RPMH_POWER_STATE);

	if (val != 0xf) {
		int ret = a6xx_gmu_wait_for_idle(a6xx_gpu);

		/* Temporary until we can recover safely */
		BUG_ON(ret);

		/* tell the GMU we want to slumber */
		a6xx_gmu_notify_slumber(gmu);

		ret = gmu_poll_timeout(gmu,
			REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS, val,
			!(val & A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS_GPUBUSYIGNAHB),
			100, 10000);

		/*
		 * Let the user know we failed to slumber but don't worry too
		 * much because we are powering down anyway
		 */

		if (ret)
			dev_err(gmu->dev,
				"Unable to slumber GMU: status = 0%x/0%x\n",
				gmu_read(gmu,
					REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS),
				gmu_read(gmu,
					REG_A6XX_GPU_GMU_AO_GPU_CX_BUSY_STATUS2));
	}

	/* Turn off HFI */
	a6xx_hfi_stop(gmu);

	/* Stop the interrupts and mask the hardware */
	a6xx_gmu_irq_disable(gmu);

	/* Tell RPMh to power off the GPU */
	a6xx_rpmh_stop(gmu);

	clk_bulk_disable_unprepare(gmu->nr_clocks, gmu->clocks);

	pm_runtime_put_sync(gmu->dev);

	return 0;
}