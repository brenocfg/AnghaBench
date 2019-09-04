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
struct ttm_buffer_object {int /*<<< orphan*/  resv; int /*<<< orphan*/  ttm_resv; } ;
struct reservation_object_list {int shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_fence {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  signaled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_enable_sw_signaling (struct dma_fence*) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_fence* reservation_object_get_excl (int /*<<< orphan*/ *) ; 
 struct reservation_object_list* reservation_object_get_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_bo_flush_all_fences(struct ttm_buffer_object *bo)
{
	struct reservation_object_list *fobj;
	struct dma_fence *fence;
	int i;

	fobj = reservation_object_get_list(&bo->ttm_resv);
	fence = reservation_object_get_excl(&bo->ttm_resv);
	if (fence && !fence->ops->signaled)
		dma_fence_enable_sw_signaling(fence);

	for (i = 0; fobj && i < fobj->shared_count; ++i) {
		fence = rcu_dereference_protected(fobj->shared[i],
					reservation_object_held(bo->resv));

		if (!fence->ops->signaled)
			dma_fence_enable_sw_signaling(fence);
	}
}