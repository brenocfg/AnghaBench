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
struct a6xx_gpu {int /*<<< orphan*/  gmu; } ;

/* Variables and functions */
 int A6XX_RBBM_INT_0_MASK_RBBM_HANG_DETECT ; 
 int A6XX_RBBM_STATUS_CP_AHB_BUSY_CX_MASTER ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_INT_0_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_RBBM_STATUS ; 
 int /*<<< orphan*/  a6xx_gmu_isidle (int /*<<< orphan*/ *) ; 
 int gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static inline bool _a6xx_check_idle(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	/* Check that the GMU is idle */
	if (!a6xx_gmu_isidle(&a6xx_gpu->gmu))
		return false;

	/* Check tha the CX master is idle */
	if (gpu_read(gpu, REG_A6XX_RBBM_STATUS) &
			~A6XX_RBBM_STATUS_CP_AHB_BUSY_CX_MASTER)
		return false;

	return !(gpu_read(gpu, REG_A6XX_RBBM_INT_0_STATUS) &
		A6XX_RBBM_INT_0_MASK_RBBM_HANG_DETECT);
}