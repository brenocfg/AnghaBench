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
struct ttm_operation_ctx {scalar_t__ resv; int flags; } ;
struct ttm_buffer_object {scalar_t__ resv; int /*<<< orphan*/  ddestroy; } ;

/* Variables and functions */
 int TTM_OPT_FLAG_ALLOW_RES_EVICT ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_assert_held (scalar_t__) ; 
 int reservation_object_trylock (scalar_t__) ; 

__attribute__((used)) static bool ttm_bo_evict_swapout_allowable(struct ttm_buffer_object *bo,
			struct ttm_operation_ctx *ctx, bool *locked)
{
	bool ret = false;

	*locked = false;
	if (bo->resv == ctx->resv) {
		reservation_object_assert_held(bo->resv);
		if (ctx->flags & TTM_OPT_FLAG_ALLOW_RES_EVICT
		    || !list_empty(&bo->ddestroy))
			ret = true;
	} else {
		*locked = reservation_object_trylock(bo->resv);
		ret = *locked;
	}

	return ret;
}