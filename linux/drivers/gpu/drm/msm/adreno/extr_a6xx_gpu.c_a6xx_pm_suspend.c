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
struct TYPE_2__ {int /*<<< orphan*/  devfreq; } ;
struct msm_gpu {TYPE_1__ devfreq; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_gpu {int dummy; } ;

/* Variables and functions */
 int a6xx_gmu_stop (struct a6xx_gpu*) ; 
 int /*<<< orphan*/  devfreq_suspend_device (int /*<<< orphan*/ ) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

__attribute__((used)) static int a6xx_pm_suspend(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);

	devfreq_suspend_device(gpu->devfreq.devfreq);

	return a6xx_gmu_stop(a6xx_gpu);
}