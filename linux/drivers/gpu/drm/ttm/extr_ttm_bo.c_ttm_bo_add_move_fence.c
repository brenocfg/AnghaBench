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
struct ttm_mem_type_manager {int /*<<< orphan*/  move_lock; int /*<<< orphan*/  move; } ;
struct ttm_mem_reg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {struct dma_fence* moving; TYPE_1__ base; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_add_shared_fence (int /*<<< orphan*/ ,struct dma_fence*) ; 
 int dma_resv_reserve_shared (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ttm_bo_add_move_fence(struct ttm_buffer_object *bo,
				 struct ttm_mem_type_manager *man,
				 struct ttm_mem_reg *mem)
{
	struct dma_fence *fence;
	int ret;

	spin_lock(&man->move_lock);
	fence = dma_fence_get(man->move);
	spin_unlock(&man->move_lock);

	if (fence) {
		dma_resv_add_shared_fence(bo->base.resv, fence);

		ret = dma_resv_reserve_shared(bo->base.resv, 1);
		if (unlikely(ret)) {
			dma_fence_put(fence);
			return ret;
		}

		dma_fence_put(bo->moving);
		bo->moving = fence;
	}

	return 0;
}