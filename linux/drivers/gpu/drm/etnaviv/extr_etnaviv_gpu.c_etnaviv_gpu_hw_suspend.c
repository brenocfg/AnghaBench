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
struct etnaviv_gpu {int exec_state; int /*<<< orphan*/ * mmu_context; int /*<<< orphan*/  lock; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  etnaviv_buffer_end (struct etnaviv_gpu*) ; 
 int etnaviv_gpu_clk_disable (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_gpu_wait_idle (struct etnaviv_gpu*,int) ; 
 int /*<<< orphan*/  etnaviv_iommu_context_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int etnaviv_gpu_hw_suspend(struct etnaviv_gpu *gpu)
{
	if (gpu->initialized && gpu->mmu_context) {
		/* Replace the last WAIT with END */
		mutex_lock(&gpu->lock);
		etnaviv_buffer_end(gpu);
		mutex_unlock(&gpu->lock);

		/*
		 * We know that only the FE is busy here, this should
		 * happen quickly (as the WAIT is only 200 cycles).  If
		 * we fail, just warn and continue.
		 */
		etnaviv_gpu_wait_idle(gpu, 100);

		etnaviv_iommu_context_put(gpu->mmu_context);
		gpu->mmu_context = NULL;
	}

	gpu->exec_state = -1;

	return etnaviv_gpu_clk_disable(gpu);
}