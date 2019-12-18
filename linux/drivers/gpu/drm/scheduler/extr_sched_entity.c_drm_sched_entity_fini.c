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
struct drm_sched_entity {int /*<<< orphan*/  rq_list; int /*<<< orphan*/ * last_scheduled; int /*<<< orphan*/ * dependency; int /*<<< orphan*/  cb; int /*<<< orphan*/  job_queue; TYPE_1__* rq; } ;
struct drm_gpu_scheduler {int /*<<< orphan*/  thread; } ;
struct TYPE_2__ {struct drm_gpu_scheduler* sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_remove_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_entity_kill_jobs (struct drm_sched_entity*) ; 
 int /*<<< orphan*/  drm_sched_rq_remove_entity (TYPE_1__*,struct drm_sched_entity*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_park (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_unpark (int /*<<< orphan*/ ) ; 
 scalar_t__ spsc_queue_count (int /*<<< orphan*/ *) ; 

void drm_sched_entity_fini(struct drm_sched_entity *entity)
{
	struct drm_gpu_scheduler *sched = NULL;

	if (entity->rq) {
		sched = entity->rq->sched;
		drm_sched_rq_remove_entity(entity->rq, entity);
	}

	/* Consumption of existing IBs wasn't completed. Forcefully
	 * remove them here.
	 */
	if (spsc_queue_count(&entity->job_queue)) {
		if (sched) {
			/* Park the kernel for a moment to make sure it isn't processing
			 * our enity.
			 */
			kthread_park(sched->thread);
			kthread_unpark(sched->thread);
		}
		if (entity->dependency) {
			dma_fence_remove_callback(entity->dependency,
						  &entity->cb);
			dma_fence_put(entity->dependency);
			entity->dependency = NULL;
		}

		drm_sched_entity_kill_jobs(entity);
	}

	dma_fence_put(entity->last_scheduled);
	entity->last_scheduled = NULL;
	kfree(entity->rq_list);
}