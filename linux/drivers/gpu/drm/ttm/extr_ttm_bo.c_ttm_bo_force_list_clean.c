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
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; int /*<<< orphan*/  flags; } ;
struct ttm_mem_type_manager {int /*<<< orphan*/  move_lock; int /*<<< orphan*/  move; int /*<<< orphan*/ * lru; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;
struct ttm_bo_device {struct ttm_bo_global* glob; struct ttm_mem_type_manager* man; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 unsigned int TTM_MAX_BO_PRIORITY ; 
 int /*<<< orphan*/  TTM_OPT_FLAG_FORCE_ALLOC ; 
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int dma_fence_wait (struct dma_fence*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ttm_mem_evict_first (struct ttm_bo_device*,unsigned int,int /*<<< orphan*/ *,struct ttm_operation_ctx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ttm_bo_force_list_clean(struct ttm_bo_device *bdev,
				   unsigned mem_type)
{
	struct ttm_operation_ctx ctx = {
		.interruptible = false,
		.no_wait_gpu = false,
		.flags = TTM_OPT_FLAG_FORCE_ALLOC
	};
	struct ttm_mem_type_manager *man = &bdev->man[mem_type];
	struct ttm_bo_global *glob = bdev->glob;
	struct dma_fence *fence;
	int ret;
	unsigned i;

	/*
	 * Can't use standard list traversal since we're unlocking.
	 */

	spin_lock(&glob->lru_lock);
	for (i = 0; i < TTM_MAX_BO_PRIORITY; ++i) {
		while (!list_empty(&man->lru[i])) {
			spin_unlock(&glob->lru_lock);
			ret = ttm_mem_evict_first(bdev, mem_type, NULL, &ctx,
						  NULL);
			if (ret)
				return ret;
			spin_lock(&glob->lru_lock);
		}
	}
	spin_unlock(&glob->lru_lock);

	spin_lock(&man->move_lock);
	fence = dma_fence_get(man->move);
	spin_unlock(&man->move_lock);

	if (fence) {
		ret = dma_fence_wait(fence, false);
		dma_fence_put(fence);
		if (ret)
			return ret;
	}

	return 0;
}