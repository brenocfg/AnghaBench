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
struct drm_sched_rq {int dummy; } ;
struct drm_sched_entity {int num_rq_list; int /*<<< orphan*/  rq_lock; struct drm_sched_rq* rq; int /*<<< orphan*/  last_scheduled; int /*<<< orphan*/  job_queue; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct dma_fence* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 struct drm_sched_rq* drm_sched_entity_get_free_sched (struct drm_sched_entity*) ; 
 int /*<<< orphan*/  drm_sched_rq_remove_entity (struct drm_sched_rq*,struct drm_sched_entity*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ spsc_queue_count (int /*<<< orphan*/ *) ; 

void drm_sched_entity_select_rq(struct drm_sched_entity *entity)
{
	struct dma_fence *fence;
	struct drm_sched_rq *rq;

	if (spsc_queue_count(&entity->job_queue) || entity->num_rq_list <= 1)
		return;

	fence = READ_ONCE(entity->last_scheduled);
	if (fence && !dma_fence_is_signaled(fence))
		return;

	rq = drm_sched_entity_get_free_sched(entity);
	if (rq == entity->rq)
		return;

	spin_lock(&entity->rq_lock);
	drm_sched_rq_remove_entity(entity->rq, entity);
	entity->rq = rq;
	spin_unlock(&entity->rq_lock);
}