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
struct msm_gpu {int nr_rings; TYPE_2__** rb; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {TYPE_1__** preempt; TYPE_2__* cur_ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  iova; } ;
struct TYPE_3__ {int /*<<< orphan*/  rbase; scalar_t__ rptr; scalar_t__ wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PREEMPT_NONE ; 
 int /*<<< orphan*/  REG_A5XX_CP_CONTEXT_SWITCH_SMMU_INFO_HI ; 
 int /*<<< orphan*/  REG_A5XX_CP_CONTEXT_SWITCH_SMMU_INFO_LO ; 
 int /*<<< orphan*/  gpu_write64 (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_preempt_state (struct a5xx_gpu*,int /*<<< orphan*/ ) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

void a5xx_preempt_hw_init(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	int i;

	/* Always come up on rb 0 */
	a5xx_gpu->cur_ring = gpu->rb[0];

	/* No preemption if we only have one ring */
	if (gpu->nr_rings == 1)
		return;

	for (i = 0; i < gpu->nr_rings; i++) {
		a5xx_gpu->preempt[i]->wptr = 0;
		a5xx_gpu->preempt[i]->rptr = 0;
		a5xx_gpu->preempt[i]->rbase = gpu->rb[i]->iova;
	}

	/* Write a 0 to signal that we aren't switching pagetables */
	gpu_write64(gpu, REG_A5XX_CP_CONTEXT_SWITCH_SMMU_INFO_LO,
		REG_A5XX_CP_CONTEXT_SWITCH_SMMU_INFO_HI, 0);

	/* Reset the preemption state */
	set_preempt_state(a5xx_gpu, PREEMPT_NONE);
}