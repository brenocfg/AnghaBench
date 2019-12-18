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
struct msm_gpu {int /*<<< orphan*/  icc_path; } ;
struct adreno_gpu {struct msm_gpu base; } ;
struct a6xx_gmu {int hung; int /*<<< orphan*/  dev; int /*<<< orphan*/  gmu_irq; int /*<<< orphan*/  gxpd; scalar_t__ nr_gpu_freqs; int /*<<< orphan*/  hfi_irq; int /*<<< orphan*/  clocks; int /*<<< orphan*/  nr_clocks; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  initialized; } ;
struct a6xx_gpu {struct a6xx_gmu gmu; struct adreno_gpu base; } ;

/* Variables and functions */
 int /*<<< orphan*/  A6XX_GMU_IRQ_MASK ; 
 int /*<<< orphan*/  A6XX_HFI_IRQ_MASK ; 
 int GMU_COLD_BOOT ; 
 int GMU_WARM_BOOT ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBps_to_icc (int) ; 
 int /*<<< orphan*/  REG_A6XX_GMU_AO_HOST_INTERRUPT_CLR ; 
 int /*<<< orphan*/  REG_A6XX_GMU_AO_HOST_INTERRUPT_MASK ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GENERAL_7 ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GMU2HOST_INTR_CLR ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GMU2HOST_INTR_MASK ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  __a6xx_gmu_set_freq (struct a6xx_gmu*,scalar_t__) ; 
 int a6xx_gmu_fw_start (struct a6xx_gmu*,int) ; 
 int a6xx_hfi_start (struct a6xx_gmu*,int) ; 
 int /*<<< orphan*/  a6xx_rpmh_stop (struct a6xx_gmu*) ; 
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int gmu_read (struct a6xx_gmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icc_set_bw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

int a6xx_gmu_resume(struct a6xx_gpu *a6xx_gpu)
{
	struct adreno_gpu *adreno_gpu = &a6xx_gpu->base;
	struct msm_gpu *gpu = &adreno_gpu->base;
	struct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	int status, ret;

	if (WARN(!gmu->initialized, "The GMU is not set up yet\n"))
		return 0;

	gmu->hung = false;

	/* Turn on the resources */
	pm_runtime_get_sync(gmu->dev);

	/* Use a known rate to bring up the GMU */
	clk_set_rate(gmu->core_clk, 200000000);
	ret = clk_bulk_prepare_enable(gmu->nr_clocks, gmu->clocks);
	if (ret) {
		pm_runtime_put(gmu->dev);
		return ret;
	}

	/* Set the bus quota to a reasonable value for boot */
	icc_set_bw(gpu->icc_path, 0, MBps_to_icc(3072));

	/* Enable the GMU interrupt */
	gmu_write(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_CLR, ~0);
	gmu_write(gmu, REG_A6XX_GMU_AO_HOST_INTERRUPT_MASK, ~A6XX_GMU_IRQ_MASK);
	enable_irq(gmu->gmu_irq);

	/* Check to see if we are doing a cold or warm boot */
	status = gmu_read(gmu, REG_A6XX_GMU_GENERAL_7) == 1 ?
		GMU_WARM_BOOT : GMU_COLD_BOOT;

	ret = a6xx_gmu_fw_start(gmu, status);
	if (ret)
		goto out;

	ret = a6xx_hfi_start(gmu, status);
	if (ret)
		goto out;

	/*
	 * Turn on the GMU firmware fault interrupt after we know the boot
	 * sequence is successful
	 */
	gmu_write(gmu, REG_A6XX_GMU_GMU2HOST_INTR_CLR, ~0);
	gmu_write(gmu, REG_A6XX_GMU_GMU2HOST_INTR_MASK, ~A6XX_HFI_IRQ_MASK);
	enable_irq(gmu->hfi_irq);

	/* Set the GPU to the highest power frequency */
	__a6xx_gmu_set_freq(gmu, gmu->nr_gpu_freqs - 1);

	/*
	 * "enable" the GX power domain which won't actually do anything but it
	 * will make sure that the refcounting is correct in case we need to
	 * bring down the GX after a GMU failure
	 */
	if (!IS_ERR_OR_NULL(gmu->gxpd))
		pm_runtime_get(gmu->gxpd);

out:
	/* On failure, shut down the GMU to leave it in a good state */
	if (ret) {
		disable_irq(gmu->gmu_irq);
		a6xx_rpmh_stop(gmu);
		pm_runtime_put(gmu->dev);
	}

	return ret;
}