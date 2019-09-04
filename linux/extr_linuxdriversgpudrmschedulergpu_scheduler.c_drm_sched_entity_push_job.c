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
struct drm_sched_job {int /*<<< orphan*/  queue_node; struct drm_gpu_scheduler* sched; } ;
struct drm_sched_entity {int /*<<< orphan*/  rq_lock; int /*<<< orphan*/  rq; int /*<<< orphan*/  job_queue; int /*<<< orphan*/  last_user; } ;
struct drm_gpu_scheduler {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  group_leader; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  drm_sched_rq_add_entity (int /*<<< orphan*/ ,struct drm_sched_entity*) ; 
 int /*<<< orphan*/  drm_sched_wakeup (struct drm_gpu_scheduler*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int spsc_queue_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drm_sched_job (struct drm_sched_job*,struct drm_sched_entity*) ; 

void drm_sched_entity_push_job(struct drm_sched_job *sched_job,
			       struct drm_sched_entity *entity)
{
	struct drm_gpu_scheduler *sched = sched_job->sched;
	bool first = false;

	trace_drm_sched_job(sched_job, entity);

	WRITE_ONCE(entity->last_user, current->group_leader);
	first = spsc_queue_push(&entity->job_queue, &sched_job->queue_node);

	/* first job wakes up scheduler */
	if (first) {
		/* Add the entity to the run queue */
		spin_lock(&entity->rq_lock);
		if (!entity->rq) {
			DRM_ERROR("Trying to push to a killed entity\n");
			spin_unlock(&entity->rq_lock);
			return;
		}
		drm_sched_rq_add_entity(entity->rq, entity);
		spin_unlock(&entity->rq_lock);
		drm_sched_wakeup(sched);
	}
}