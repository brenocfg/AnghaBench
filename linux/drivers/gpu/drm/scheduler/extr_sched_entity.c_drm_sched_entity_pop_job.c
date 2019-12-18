#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_sched_job {TYPE_3__* s_fence; } ;
struct drm_sched_entity {int /*<<< orphan*/  job_queue; int /*<<< orphan*/  last_scheduled; scalar_t__ guilty; int /*<<< orphan*/  dependency; TYPE_1__* rq; } ;
struct drm_gpu_scheduler {TYPE_2__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  finished; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* dependency ) (struct drm_sched_job*,struct drm_sched_entity*) ;} ;
struct TYPE_4__ {struct drm_gpu_scheduler* sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECANCELED ; 
 scalar_t__ atomic_read (scalar_t__) ; 
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_sched_entity_add_dependency_cb (struct drm_sched_entity*) ; 
 int /*<<< orphan*/  spsc_queue_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spsc_queue_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_sched_job*,struct drm_sched_entity*) ; 
 struct drm_sched_job* to_drm_sched_job (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_drm_sched_job_wait_dep (struct drm_sched_job*,int /*<<< orphan*/ ) ; 

struct drm_sched_job *drm_sched_entity_pop_job(struct drm_sched_entity *entity)
{
	struct drm_gpu_scheduler *sched = entity->rq->sched;
	struct drm_sched_job *sched_job;

	sched_job = to_drm_sched_job(spsc_queue_peek(&entity->job_queue));
	if (!sched_job)
		return NULL;

	while ((entity->dependency =
			sched->ops->dependency(sched_job, entity))) {
		trace_drm_sched_job_wait_dep(sched_job, entity->dependency);

		if (drm_sched_entity_add_dependency_cb(entity))
			return NULL;
	}

	/* skip jobs from entity that marked guilty */
	if (entity->guilty && atomic_read(entity->guilty))
		dma_fence_set_error(&sched_job->s_fence->finished, -ECANCELED);

	dma_fence_put(entity->last_scheduled);
	entity->last_scheduled = dma_fence_get(&sched_job->s_fence->finished);

	spsc_queue_pop(&entity->job_queue);
	return sched_job;
}