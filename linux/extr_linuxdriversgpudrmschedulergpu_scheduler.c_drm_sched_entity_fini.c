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
struct drm_sched_job {int /*<<< orphan*/  finish_cb; struct drm_sched_fence* s_fence; } ;
struct drm_sched_fence {int /*<<< orphan*/  finished; } ;
struct drm_sched_entity {int /*<<< orphan*/ * last_scheduled; int /*<<< orphan*/  job_queue; int /*<<< orphan*/ * dependency; int /*<<< orphan*/  cb; TYPE_1__* rq; } ;
struct drm_gpu_scheduler {int /*<<< orphan*/  thread; } ;
struct TYPE_2__ {struct drm_gpu_scheduler* sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  ESRCH ; 
 int dma_fence_add_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_remove_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sched_entity_kill_jobs_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_fence_scheduled (struct drm_sched_fence*) ; 
 int /*<<< orphan*/  drm_sched_rq_remove_entity (TYPE_1__*,struct drm_sched_entity*) ; 
 int /*<<< orphan*/  kthread_park (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_unpark (int /*<<< orphan*/ ) ; 
 scalar_t__ spsc_queue_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spsc_queue_pop (int /*<<< orphan*/ *) ; 
 struct drm_sched_job* to_drm_sched_job (int /*<<< orphan*/ ) ; 

void drm_sched_entity_fini(struct drm_sched_entity *entity)
{
	struct drm_gpu_scheduler *sched;

	sched = entity->rq->sched;
	drm_sched_rq_remove_entity(entity->rq, entity);

	/* Consumption of existing IBs wasn't completed. Forcefully
	 * remove them here.
	 */
	if (spsc_queue_peek(&entity->job_queue)) {
		struct drm_sched_job *job;
		int r;

		/* Park the kernel for a moment to make sure it isn't processing
		 * our enity.
		 */
		kthread_park(sched->thread);
		kthread_unpark(sched->thread);
		if (entity->dependency) {
			dma_fence_remove_callback(entity->dependency,
						  &entity->cb);
			dma_fence_put(entity->dependency);
			entity->dependency = NULL;
		}

		while ((job = to_drm_sched_job(spsc_queue_pop(&entity->job_queue)))) {
			struct drm_sched_fence *s_fence = job->s_fence;
			drm_sched_fence_scheduled(s_fence);
			dma_fence_set_error(&s_fence->finished, -ESRCH);

			/*
			 * When pipe is hanged by older entity, new entity might
			 * not even have chance to submit it's first job to HW
			 * and so entity->last_scheduled will remain NULL
			 */
			if (!entity->last_scheduled) {
				drm_sched_entity_kill_jobs_cb(NULL, &job->finish_cb);
			} else {
				r = dma_fence_add_callback(entity->last_scheduled, &job->finish_cb,
								drm_sched_entity_kill_jobs_cb);
				if (r == -ENOENT)
					drm_sched_entity_kill_jobs_cb(NULL, &job->finish_cb);
				else if (r)
					DRM_ERROR("fence add callback failed (%d)\n", r);
			}
		}
	}

	dma_fence_put(entity->last_scheduled);
	entity->last_scheduled = NULL;
}