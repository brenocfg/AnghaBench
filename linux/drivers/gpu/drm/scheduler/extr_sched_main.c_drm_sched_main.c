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
struct sched_param {int sched_priority; } ;
struct drm_sched_job {int /*<<< orphan*/  cb; struct drm_sched_fence* s_fence; } ;
struct drm_sched_fence {int /*<<< orphan*/  finished; int /*<<< orphan*/  parent; } ;
struct drm_sched_entity {int dummy; } ;
struct drm_gpu_scheduler {int /*<<< orphan*/  job_scheduled; TYPE_1__* ops; int /*<<< orphan*/  hw_rq_count; int /*<<< orphan*/  wake_up_worker; } ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {struct dma_fence* (* run_job ) (struct drm_sched_job*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct dma_fence*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dma_fence*) ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct dma_fence*,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_blocked (struct drm_gpu_scheduler*) ; 
 int /*<<< orphan*/  drm_sched_cleanup_jobs (struct drm_gpu_scheduler*) ; 
 struct drm_sched_job* drm_sched_entity_pop_job (struct drm_sched_entity*) ; 
 int /*<<< orphan*/  drm_sched_fence_scheduled (struct drm_sched_fence*) ; 
 int /*<<< orphan*/  drm_sched_job_begin (struct drm_sched_job*) ; 
 int /*<<< orphan*/  drm_sched_process_job (struct dma_fence*,int /*<<< orphan*/ *) ; 
 struct drm_sched_entity* drm_sched_select_entity (struct drm_gpu_scheduler*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 struct dma_fence* stub1 (struct drm_sched_job*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_sched_main(void *param)
{
	struct sched_param sparam = {.sched_priority = 1};
	struct drm_gpu_scheduler *sched = (struct drm_gpu_scheduler *)param;
	int r;

	sched_setscheduler(current, SCHED_FIFO, &sparam);

	while (!kthread_should_stop()) {
		struct drm_sched_entity *entity = NULL;
		struct drm_sched_fence *s_fence;
		struct drm_sched_job *sched_job;
		struct dma_fence *fence;

		wait_event_interruptible(sched->wake_up_worker,
					 (drm_sched_cleanup_jobs(sched),
					 (!drm_sched_blocked(sched) &&
					  (entity = drm_sched_select_entity(sched))) ||
					 kthread_should_stop()));

		if (!entity)
			continue;

		sched_job = drm_sched_entity_pop_job(entity);
		if (!sched_job)
			continue;

		s_fence = sched_job->s_fence;

		atomic_inc(&sched->hw_rq_count);
		drm_sched_job_begin(sched_job);

		fence = sched->ops->run_job(sched_job);
		drm_sched_fence_scheduled(s_fence);

		if (!IS_ERR_OR_NULL(fence)) {
			s_fence->parent = dma_fence_get(fence);
			r = dma_fence_add_callback(fence, &sched_job->cb,
						   drm_sched_process_job);
			if (r == -ENOENT)
				drm_sched_process_job(fence, &sched_job->cb);
			else if (r)
				DRM_ERROR("fence add callback failed (%d)\n",
					  r);
			dma_fence_put(fence);
		} else {

			dma_fence_set_error(&s_fence->finished, PTR_ERR(fence));
			drm_sched_process_job(NULL, &sched_job->cb);
		}

		wake_up(&sched->job_scheduled);
	}
	return 0;
}