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
struct msm_gpu {int dummy; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_gpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_A6XX_VBIF_XIN_HALT_CTRL0 ; 
 int /*<<< orphan*/  REG_A6XX_VBIF_XIN_HALT_CTRL1 ; 
 int a6xx_gmu_stop (struct a6xx_gpu*) ; 
 int /*<<< orphan*/  a6xx_gmu_wait_for_idle (struct a6xx_gpu*) ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_until (int) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int a6xx_pm_suspend(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	/*
	 * Make sure the GMU is idle before continuing (because some transitions
	 * may use VBIF
	 */
	a6xx_gmu_wait_for_idle(a6xx_gpu);

	/* Clear the VBIF pipe before shutting down */
	/* FIXME: This accesses the GPU - do we need to make sure it is on? */
	gpu_write(gpu, REG_A6XX_VBIF_XIN_HALT_CTRL0, 0xf);
	spin_until((gpu_read(gpu, REG_A6XX_VBIF_XIN_HALT_CTRL1) & 0xf) == 0xf);
	gpu_write(gpu, REG_A6XX_VBIF_XIN_HALT_CTRL0, 0);

	return a6xx_gmu_stop(a6xx_gpu);
}