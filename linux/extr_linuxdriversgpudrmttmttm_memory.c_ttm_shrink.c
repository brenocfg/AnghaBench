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
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_operation_ctx {int dummy; } ;
struct ttm_mem_global {int /*<<< orphan*/  lock; int /*<<< orphan*/  bo_glob; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ttm_bo_swapout (int /*<<< orphan*/ ,struct ttm_operation_ctx*) ; 
 scalar_t__ ttm_zones_above_swap_target (struct ttm_mem_global*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ttm_shrink(struct ttm_mem_global *glob, bool from_wq,
			uint64_t extra, struct ttm_operation_ctx *ctx)
{
	int ret;

	spin_lock(&glob->lock);

	while (ttm_zones_above_swap_target(glob, from_wq, extra)) {
		spin_unlock(&glob->lock);
		ret = ttm_bo_swapout(glob->bo_glob, ctx);
		spin_lock(&glob->lock);
		if (unlikely(ret != 0))
			break;
	}

	spin_unlock(&glob->lock);
}