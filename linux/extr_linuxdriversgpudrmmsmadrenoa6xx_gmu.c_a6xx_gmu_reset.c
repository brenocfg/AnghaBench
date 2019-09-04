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
struct a6xx_gmu {scalar_t__ nr_gpu_freqs; int /*<<< orphan*/  clocks; int /*<<< orphan*/  nr_clocks; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  gx; } ;
struct a6xx_gpu {struct a6xx_gmu gmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMU_COLD_BOOT ; 
 int /*<<< orphan*/  GMU_OOB_BOOT_SLUMBER ; 
 int /*<<< orphan*/  GMU_RESET ; 
 int /*<<< orphan*/  REG_A6XX_RSCC_TCS0_DRV0_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_RSCC_TCS1_DRV0_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_RSCC_TCS2_DRV0_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_RSCC_TCS3_DRV0_STATUS ; 
 int /*<<< orphan*/  a6xx_gmu_clear_oob (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int a6xx_gmu_fw_start (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_gmu_irq_disable (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_gmu_irq_enable (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_gmu_set_freq (struct a6xx_gmu*,scalar_t__) ; 
 int a6xx_hfi_start (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_hfi_stop (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_sptprac_disable (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gmu_poll_timeout (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_force_disable (int /*<<< orphan*/ ) ; 

int a6xx_gmu_reset(struct a6xx_gpu *a6xx_gpu)
{
	struct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	int ret;
	u32 val;

	/* Flush all the queues */
	a6xx_hfi_stop(gmu);

	/* Stop the interrupts */
	a6xx_gmu_irq_disable(gmu);

	/* Force off SPTP in case the GMU is managing it */
	a6xx_sptprac_disable(gmu);

	/* Make sure there are no outstanding RPMh votes */
	gmu_poll_timeout(gmu, REG_A6XX_RSCC_TCS0_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_timeout(gmu, REG_A6XX_RSCC_TCS1_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_timeout(gmu, REG_A6XX_RSCC_TCS2_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_timeout(gmu, REG_A6XX_RSCC_TCS3_DRV0_STATUS, val,
		(val & 1), 100, 1000);

	/* Force off the GX GSDC */
	regulator_force_disable(gmu->gx);

	/* Disable the resources */
	clk_bulk_disable_unprepare(gmu->nr_clocks, gmu->clocks);
	pm_runtime_put_sync(gmu->dev);

	/* Re-enable the resources */
	pm_runtime_get_sync(gmu->dev);

	/* Use a known rate to bring up the GMU */
	clk_set_rate(gmu->core_clk, 200000000);
	ret = clk_bulk_prepare_enable(gmu->nr_clocks, gmu->clocks);
	if (ret)
		goto out;

	a6xx_gmu_irq_enable(gmu);

	ret = a6xx_gmu_fw_start(gmu, GMU_RESET);
	if (!ret)
		ret = a6xx_hfi_start(gmu, GMU_COLD_BOOT);

	/* Set the GPU back to the highest power frequency */
	a6xx_gmu_set_freq(gmu, gmu->nr_gpu_freqs - 1);

out:
	if (ret)
		a6xx_gmu_clear_oob(gmu, GMU_OOB_BOOT_SLUMBER);

	return ret;
}