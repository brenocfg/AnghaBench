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
struct msm_gpu {int nr_rings; int /*<<< orphan*/ * rb; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {int /*<<< orphan*/  preempt_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  a5xx_preempt_fini (struct msm_gpu*) ; 
 int /*<<< orphan*/  a5xx_preempt_timer ; 
 scalar_t__ preempt_init_ring (struct a5xx_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 

void a5xx_preempt_init(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	int i;

	/* No preemption if we only have one ring */
	if (gpu->nr_rings <= 1)
		return;

	for (i = 0; i < gpu->nr_rings; i++) {
		if (preempt_init_ring(a5xx_gpu, gpu->rb[i])) {
			/*
			 * On any failure our adventure is over. Clean up and
			 * set nr_rings to 1 to force preemption off
			 */
			a5xx_preempt_fini(gpu);
			gpu->nr_rings = 1;

			return;
		}
	}

	timer_setup(&a5xx_gpu->preempt_timer, a5xx_preempt_timer, 0);
}