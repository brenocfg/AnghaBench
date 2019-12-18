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
struct msm_gpu {int dummy; } ;
struct adreno_gpu {int dummy; } ;
struct a6xx_gmu {unsigned long freq; int nr_gpu_freqs; unsigned long* gpu_freqs; } ;
struct a6xx_gpu {struct a6xx_gmu gmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __a6xx_gmu_set_freq (struct a6xx_gmu*,int) ; 
 struct a6xx_gpu* to_a6xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

void a6xx_gmu_set_freq(struct msm_gpu *gpu, unsigned long freq)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a6xx_gpu *a6xx_gpu = to_a6xx_gpu(adreno_gpu);
	struct a6xx_gmu *gmu = &a6xx_gpu->gmu;
	u32 perf_index = 0;

	if (freq == gmu->freq)
		return;

	for (perf_index = 0; perf_index < gmu->nr_gpu_freqs - 1; perf_index++)
		if (freq == gmu->gpu_freqs[perf_index])
			break;

	__a6xx_gmu_set_freq(gmu, perf_index);
}