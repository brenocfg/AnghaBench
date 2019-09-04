#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_5__ {int /*<<< orphan*/  thread; } ;
struct etnaviv_gpu {void* hangcheck_dma_addr; TYPE_2__ sched; } ;
struct etnaviv_gem_submit {int /*<<< orphan*/  out_fence; struct etnaviv_gpu* gpu; } ;
struct drm_sched_job {TYPE_1__* sched; int /*<<< orphan*/  work_tdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIVS_FE_DMA_ADDRESS ; 
 scalar_t__ dma_fence_is_signaled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_hw_job_reset (TYPE_2__*,struct drm_sched_job*) ; 
 int /*<<< orphan*/  drm_sched_job_recovery (TYPE_2__*) ; 
 int /*<<< orphan*/  etnaviv_core_dump (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_gpu_recover_hang (struct etnaviv_gpu*) ; 
 void* gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_park (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_unpark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
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
		schedule_delayed_work(&sched_job->work_tdr,
				      sched_job->sched->timeout);
		return;
	}

	/* block scheduler */
	kthread_park(gpu->sched.thread);
	drm_sched_hw_job_reset(&gpu->sched, sched_job);

	/* get the GPU back into the init state */
	etnaviv_core_dump(gpu);
	etnaviv_gpu_recover_hang(gpu);

	/* restart scheduler after GPU is usable again */
	drm_sched_job_recovery(&gpu->sched);
	kthread_unpark(gpu->sched.thread);
}