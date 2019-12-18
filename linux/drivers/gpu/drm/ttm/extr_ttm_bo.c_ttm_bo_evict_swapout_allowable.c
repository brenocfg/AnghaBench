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
struct ttm_operation_ctx {scalar_t__ resv; int flags; } ;
struct TYPE_2__ {scalar_t__ resv; } ;
struct ttm_buffer_object {TYPE_1__ base; int /*<<< orphan*/  ddestroy; } ;

/* Variables and functions */
 int TTM_OPT_FLAG_ALLOW_RES_EVICT ; 
 int /*<<< orphan*/  dma_resv_assert_held (scalar_t__) ; 
 int dma_resv_trylock (scalar_t__) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ttm_bo_evict_swapout_allowable(struct ttm_buffer_object *bo,
			struct ttm_operation_ctx *ctx, bool *locked, bool *busy)
{
	bool ret = false;

	if (bo->base.resv == ctx->resv) {
		dma_resv_assert_held(bo->base.resv);
		if (ctx->flags & TTM_OPT_FLAG_ALLOW_RES_EVICT
		    || !list_empty(&bo->ddestroy))
			ret = true;
		*locked = false;
		if (busy)
			*busy = false;
	} else {
		ret = dma_resv_trylock(bo->base.resv);
		*locked = ret;
		if (busy)
			*busy = !ret;
	}

	return ret;
}