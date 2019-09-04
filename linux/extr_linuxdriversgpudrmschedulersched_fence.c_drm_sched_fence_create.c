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
struct drm_sched_fence {int /*<<< orphan*/  lock; int /*<<< orphan*/  finished; int /*<<< orphan*/  scheduled; int /*<<< orphan*/  sched; void* owner; } ;
struct drm_sched_entity {scalar_t__ fence_context; int /*<<< orphan*/  fence_seq; TYPE_1__* rq; } ;
struct TYPE_2__ {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  drm_sched_fence_ops_finished ; 
 int /*<<< orphan*/  drm_sched_fence_ops_scheduled ; 
 struct drm_sched_fence* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_fence_slab ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct drm_sched_fence *drm_sched_fence_create(struct drm_sched_entity *entity,
					       void *owner)
{
	struct drm_sched_fence *fence = NULL;
	unsigned seq;

	fence = kmem_cache_zalloc(sched_fence_slab, GFP_KERNEL);
	if (fence == NULL)
		return NULL;

	fence->owner = owner;
	fence->sched = entity->rq->sched;
	spin_lock_init(&fence->lock);

	seq = atomic_inc_return(&entity->fence_seq);
	dma_fence_init(&fence->scheduled, &drm_sched_fence_ops_scheduled,
		       &fence->lock, entity->fence_context, seq);
	dma_fence_init(&fence->finished, &drm_sched_fence_ops_finished,
		       &fence->lock, entity->fence_context + 1, seq);

	return fence;
}