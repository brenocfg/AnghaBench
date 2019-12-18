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
typedef  int /*<<< orphan*/  uint64_t ;
struct msm_gpu {int dummy; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_gpu {int /*<<< orphan*/  gmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMU_OOB_GPU_SET ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_PERFCTR_CP_0_HI ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_PERFCTR_CP_0_LO ; 
 int /*<<< orphan*/  a6xx_gmu_clear_oob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a6xx_gmu_set_oob (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_read64 (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int a6xx_get_timestamp(struct msm_gpu *gpu, uint64_t *value)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	/* Force the GPU power on so we can read this register */
	a6xx_gmu_set_oob(&a6xx_gpu->gmu, GMU_OOB_GPU_SET);

	*value = gpu_read64(gpu, REG_A6XX_RBBM_PERFCTR_CP_0_LO,
		REG_A6XX_RBBM_PERFCTR_CP_0_HI);

	a6xx_gmu_clear_oob(&a6xx_gpu->gmu, GMU_OOB_GPU_SET);
	return 0;
}