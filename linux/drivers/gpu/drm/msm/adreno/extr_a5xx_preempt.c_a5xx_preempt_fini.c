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
struct msm_gpu {int nr_rings; int /*<<< orphan*/  aspace; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {int /*<<< orphan*/ * preempt_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_gem_kernel_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

void a5xx_preempt_fini(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	int i;

	for (i = 0; i < gpu->nr_rings; i++)
		msm_gem_kernel_put(a5xx_gpu->preempt_bo[i], gpu->aspace, true);
}