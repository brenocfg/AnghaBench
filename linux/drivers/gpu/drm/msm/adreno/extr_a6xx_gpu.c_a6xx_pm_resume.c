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
struct msm_gpu {int needs_hw_init; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_gpu {int dummy; } ;

/* Variables and functions */
 int a6xx_gmu_resume (struct a6xx_gpu*) ; 
 int /*<<< orphan*/  msm_gpu_resume_devfreq (struct msm_gpu*) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int a6xx_pm_resume(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	int ret;

	gpu->needs_hw_init = true;

	ret = a6xx_gmu_resume(a6xx_gpu);
	if (ret)
		return ret;

	msm_gpu_resume_devfreq(gpu);

	return 0;
}