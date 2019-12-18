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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_placement {int dummy; } ;
struct ttm_operation_ctx {int dummy; } ;
struct TYPE_4__ {scalar_t__ mem_type; int /*<<< orphan*/  placement; } ;
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {int /*<<< orphan*/ * ttm; TYPE_2__ mem; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_MASK_MEMTYPE ; 
 scalar_t__ TTM_PL_SYSTEM ; 
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_mem_compat (struct ttm_placement*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ttm_bo_move_buffer (struct ttm_buffer_object*,struct ttm_placement*,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_flag_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ttm_tt_create (struct ttm_buffer_object*,int) ; 

int ttm_bo_validate(struct ttm_buffer_object *bo,
		    struct ttm_placement *placement,
		    struct ttm_operation_ctx *ctx)
{
	int ret;
	uint32_t new_flags;

	dma_resv_assert_held(bo->base.resv);
	/*
	 * Check whether we need to move buffer.
	 */
	if (!ttm_bo_mem_compat(placement, &bo->mem, &new_flags)) {
		ret = ttm_bo_move_buffer(bo, placement, ctx);
		if (ret)
			return ret;
	} else {
		/*
		 * Use the access and other non-mapping-related flag bits from
		 * the compatible memory placement flags to the active flags
		 */
		ttm_flag_masked(&bo->mem.placement, new_flags,
				~TTM_PL_MASK_MEMTYPE);
	}
	/*
	 * We might need to add a TTM.
	 */
	if (bo->mem.mem_type == TTM_PL_SYSTEM && bo->ttm == NULL) {
		ret = ttm_tt_create(bo, true);
		if (ret)
			return ret;
	}
	return 0;
}