#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msm_gpu {TYPE_1__* funcs; TYPE_2__* pdev; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_gpu {int /*<<< orphan*/  gmu; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pm_resume ) (struct msm_gpu*) ;int /*<<< orphan*/  (* pm_suspend ) (struct msm_gpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_INFO (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_A6XX_CP_SCRATCH_REG (int) ; 
 int /*<<< orphan*/  REG_A6XX_GMU_GMU_PWR_COL_KEEPALIVE ; 
 int /*<<< orphan*/  a6xx_dump (struct msm_gpu*) ; 
 int /*<<< orphan*/  adreno_dump_info (struct msm_gpu*) ; 
 int /*<<< orphan*/  gmu_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ hang_debug ; 
 int /*<<< orphan*/  msm_gpu_hw_init (struct msm_gpu*) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*) ; 
 int /*<<< orphan*/  stub2 (struct msm_gpu*) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static void a6xx_recover(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	int i;

	adreno_dump_info(gpu);

	for (i = 0; i < 8; i++)
		DRM_DEV_INFO(&gpu->pdev->dev, "CP_SCRATCH_REG%d: %u\n", i,
			gpu_read(gpu, REG_A6XX_CP_SCRATCH_REG(i)));

	if (hang_debug)
		a6xx_dump(gpu);

	/*
	 * Turn off keep alive that might have been enabled by the hang
	 * interrupt
	 */
	gmu_write(&a6xx_gpu->gmu, REG_A6XX_GMU_GMU_PWR_COL_KEEPALIVE, 0);

	gpu->funcs->pm_suspend(gpu);
	gpu->funcs->pm_resume(gpu);

	msm_gpu_hw_init(gpu);
}