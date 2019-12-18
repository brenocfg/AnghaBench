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
typedef  void* u32 ;
struct etnaviv_gpu {void* hangcheck_dma_addr; int /*<<< orphan*/  sched; } ;
struct etnaviv_gem_submit {int /*<<< orphan*/  out_fence; struct etnaviv_gpu* gpu; } ;
struct drm_sched_job {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIVS_FE_DMA_ADDRESS ; 
 scalar_t__ dma_fence_is_signaled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_increase_karma (struct drm_sched_job*) ; 
 int /*<<< orphan*/  drm_sched_resubmit_jobs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_start (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_sched_stop (int /*<<< orphan*/ *,struct drm_sched_job*) ; 
 int /*<<< orphan*/  etnaviv_core_dump (struct etnaviv_gem_submit*) ; 
 int /*<<< orphan*/  etnaviv_gpu_recover_hang (struct etnaviv_gpu*) ; 
 void* gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 struct etnaviv_gem_submit* to_etnaviv_submit (struct drm_sched_job*) ; 

__attribute__((used)) static void etnaviv_sched_timedout_job(struct drm_sched_job *sched_job)
{
	struct etnaviv_gem_submit *submit = to_etnaviv_submit(sched_job);
	struct etnaviv_gpu *gpu = submit->gpu;
	u32 dma_addr;
	int change;

	/*
	 * If the GPU managed to complete this jobs fence, the timout is
	 * spurious. Bail out.
	 */
	if (dma_fence_is_signaled(submit->out_fence))
		return;

	/*
	 * If the GPU is still making forward progress on the front-end (which
	 * should never loop) we shift out the timeout to give it a chance to
	 * finish the job.
	 */
	dma_addr = gpu_read(gpu, VIVS_FE_DMA_ADDRESS);
	change = dma_addr - gpu->hangcheck_dma_addr;
	if (change < 0 || change > 16) {
		gpu->hangcheck_dma_addr = dma_addr;
		return;
	}

	/* block scheduler */
	drm_sched_stop(&gpu->sched, sched_job);

	if(sched_job)
		drm_sched_increase_karma(sched_job);

	/* get the GPU back into the init state */
	etnaviv_core_dump(submit);
	etnaviv_gpu_recover_hang(gpu);

	drm_sched_resubmit_jobs(&gpu->sched);

	/* restart scheduler after GPU is usable again */
	drm_sched_start(&gpu->sched, true);
}