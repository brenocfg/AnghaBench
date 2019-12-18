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
struct etnaviv_gpu {int /*<<< orphan*/  lock; TYPE_1__* event; scalar_t__ mmu_context; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ user_size; } ;
struct etnaviv_gem_submit {int runtime_resumed; int /*<<< orphan*/  refcount; scalar_t__ nr_pmrs; TYPE_2__ cmdbuf; scalar_t__ mmu_context; int /*<<< orphan*/  exec_state; scalar_t__ prev_mmu_context; struct etnaviv_gpu* gpu; } ;
struct dma_fence {int dummy; } ;
struct TYPE_3__ {struct etnaviv_gem_submit* submit; int /*<<< orphan*/ * sync_point; struct dma_fence* fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  etnaviv_buffer_queue (struct etnaviv_gpu*,int /*<<< orphan*/ ,scalar_t__,unsigned int,TYPE_2__*) ; 
 struct dma_fence* etnaviv_gpu_fence_alloc (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_gpu_start_fe_idleloop (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_iommu_context_get (scalar_t__) ; 
 int /*<<< orphan*/  etnaviv_sync_point_queue (struct etnaviv_gpu*,unsigned int) ; 
 int event_alloc (struct etnaviv_gpu*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  event_free (struct etnaviv_gpu*,unsigned int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_point_perfmon_sample_post ; 
 int /*<<< orphan*/  sync_point_perfmon_sample_pre ; 

struct dma_fence *etnaviv_gpu_submit(struct etnaviv_gem_submit *submit)
{
	struct etnaviv_gpu *gpu = submit->gpu;
	struct dma_fence *gpu_fence;
	unsigned int i, nr_events = 1, event[3];
	int ret;

	if (!submit->runtime_resumed) {
		ret = pm_runtime_get_sync(gpu->dev);
		if (ret < 0)
			return NULL;
		submit->runtime_resumed = true;
	}

	/*
	 * if there are performance monitor requests we need to have
	 * - a sync point to re-configure gpu and process ETNA_PM_PROCESS_PRE
	 *   requests.
	 * - a sync point to re-configure gpu, process ETNA_PM_PROCESS_POST requests
	 *   and update the sequence number for userspace.
	 */
	if (submit->nr_pmrs)
		nr_events = 3;

	ret = event_alloc(gpu, nr_events, event);
	if (ret) {
		DRM_ERROR("no free events\n");
		return NULL;
	}

	mutex_lock(&gpu->lock);

	gpu_fence = etnaviv_gpu_fence_alloc(gpu);
	if (!gpu_fence) {
		for (i = 0; i < nr_events; i++)
			event_free(gpu, event[i]);

		goto out_unlock;
	}

	if (!gpu->mmu_context) {
		etnaviv_iommu_context_get(submit->mmu_context);
		gpu->mmu_context = submit->mmu_context;
		etnaviv_gpu_start_fe_idleloop(gpu);
	} else {
		etnaviv_iommu_context_get(gpu->mmu_context);
		submit->prev_mmu_context = gpu->mmu_context;
	}

	if (submit->nr_pmrs) {
		gpu->event[event[1]].sync_point = &sync_point_perfmon_sample_pre;
		kref_get(&submit->refcount);
		gpu->event[event[1]].submit = submit;
		etnaviv_sync_point_queue(gpu, event[1]);
	}

	gpu->event[event[0]].fence = gpu_fence;
	submit->cmdbuf.user_size = submit->cmdbuf.size - 8;
	etnaviv_buffer_queue(gpu, submit->exec_state, submit->mmu_context,
			     event[0], &submit->cmdbuf);

	if (submit->nr_pmrs) {
		gpu->event[event[2]].sync_point = &sync_point_perfmon_sample_post;
		kref_get(&submit->refcount);
		gpu->event[event[2]].submit = submit;
		etnaviv_sync_point_queue(gpu, event[2]);
	}

out_unlock:
	mutex_unlock(&gpu->lock);

	return gpu_fence;
}