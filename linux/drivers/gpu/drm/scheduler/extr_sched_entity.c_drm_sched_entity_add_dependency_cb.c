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
struct drm_sched_fence {int /*<<< orphan*/  scheduled; struct drm_gpu_scheduler* sched; } ;
struct drm_sched_entity {scalar_t__ fence_context; struct dma_fence* dependency; int /*<<< orphan*/  cb; TYPE_1__* rq; } ;
struct drm_gpu_scheduler {int dummy; } ;
struct dma_fence {scalar_t__ context; } ;
struct TYPE_2__ {struct drm_gpu_scheduler* sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  drm_sched_entity_clear_dep ; 
 int /*<<< orphan*/  drm_sched_entity_wakeup ; 
 struct drm_sched_fence* to_drm_sched_fence (struct dma_fence*) ; 

__attribute__((used)) static bool drm_sched_entity_add_dependency_cb(struct drm_sched_entity *entity)
{
	struct drm_gpu_scheduler *sched = entity->rq->sched;
	struct dma_fence *fence = entity->dependency;
	struct drm_sched_fence *s_fence;

	if (fence->context == entity->fence_context ||
	    fence->context == entity->fence_context + 1) {
		/*
		 * Fence is a scheduled/finished fence from a job
		 * which belongs to the same entity, we can ignore
		 * fences from ourself
		 */
		dma_fence_put(entity->dependency);
		return false;
	}

	s_fence = to_drm_sched_fence(fence);
	if (s_fence && s_fence->sched == sched) {

		/*
		 * Fence is from the same scheduler, only need to wait for
		 * it to be scheduled
		 */
		fence = dma_fence_get(&s_fence->scheduled);
		dma_fence_put(entity->dependency);
		entity->dependency = fence;
		if (!dma_fence_add_callback(fence, &entity->cb,
					    drm_sched_entity_clear_dep))
			return true;

		/* Ignore it when it is already scheduled */
		dma_fence_put(fence);
		return false;
	}

	if (!dma_fence_add_callback(entity->dependency, &entity->cb,
				    drm_sched_entity_wakeup))
		return true;

	dma_fence_put(entity->dependency);
	return false;
}