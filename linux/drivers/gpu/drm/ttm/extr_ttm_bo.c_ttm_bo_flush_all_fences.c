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
struct TYPE_4__ {int /*<<< orphan*/  resv; int /*<<< orphan*/  _resv; } ;
struct ttm_buffer_object {TYPE_2__ base; } ;
struct dma_resv_list {int shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_fence {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  signaled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_enable_sw_signaling (struct dma_fence*) ; 
 struct dma_fence* dma_resv_get_excl (int /*<<< orphan*/ *) ; 
 struct dma_resv_list* dma_resv_get_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_resv_held (int /*<<< orphan*/ ) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_bo_flush_all_fences(struct ttm_buffer_object *bo)
{
	struct dma_resv_list *fobj;
	struct dma_fence *fence;
	int i;

	fobj = dma_resv_get_list(&bo->base._resv);
	fence = dma_resv_get_excl(&bo->base._resv);
	if (fence && !fence->ops->signaled)
		dma_fence_enable_sw_signaling(fence);

	for (i = 0; fobj && i < fobj->shared_count; ++i) {
		fence = rcu_dereference_protected(fobj->shared[i],
					dma_resv_held(bo->base.resv));

		if (!fence->ops->signaled)
			dma_fence_enable_sw_signaling(fence);
	}
}