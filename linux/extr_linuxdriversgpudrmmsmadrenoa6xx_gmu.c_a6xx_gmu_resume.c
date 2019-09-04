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
struct a6xx_gmu {scalar_t__ nr_gpu_freqs; int /*<<< orphan*/  clocks; int /*<<< orphan*/  nr_clocks; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  mmio; } ;
struct a6xx_gpu {struct a6xx_gmu gmu; } ;

/* Variables and functions */
 int GMU_COLD_BOOT ; 
 int /*<<< orphan*/  GMU_OOB_BOOT_SLUMBER ; 
 int GMU_WARM_BOOT ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GENERAL_7 ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  a6xx_gmu_clear_oob (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int a6xx_gmu_fw_start (struct a6xx_gmu*,int) ; 
 int /*<<< orphan*/  a6xx_gmu_irq_enable (struct a6xx_gmu*) ; 
 int /*<<< orphan*/  a6xx_gmu_set_freq (struct a6xx_gmu*,scalar_t__) ; 
 int a6xx_hfi_start (struct a6xx_gmu*,int) ; 
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

int a6xx_gmu_resume(struct a6xx_gpu *a6xx_gpu)
{
	struct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	int status, ret;

	if (WARN(!gmu->mmio, "The GMU is not set up yet\n"))
		return 0;

	/* Turn on the resources */
	pm_runtime_get_sync(gmu->dev);

	/* Use a known rate to bring up the GMU */
	clk_set_rate(gmu->core_clk, 200000000);
	ret = clk_bulk_prepare_enable(gmu->nr_clocks, gmu->clocks);
	if (ret)
		goto out;

	a6xx_gmu_irq_enable(gmu);

	/* Check to see if we are doing a cold or warm boot */
	status = gmu_read(gmu, REG_A6XX_GMU_GENERAL_7) == 1 ?
		GMU_WARM_BOOT : GMU_COLD_BOOT;

	ret = a6xx_gmu_fw_start(gmu, status);
	if (ret)
		goto out;

	ret = a6xx_hfi_start(gmu, status);

	/* Set the GPU to the highest power frequency */
	a6xx_gmu_set_freq(gmu, gmu->nr_gpu_freqs - 1);

out:
	/* Make sure to turn off the boot OOB request on error */
	if (ret)
		a6xx_gmu_clear_oob(gmu, GMU_OOB_BOOT_SLUMBER);

	return ret;
}