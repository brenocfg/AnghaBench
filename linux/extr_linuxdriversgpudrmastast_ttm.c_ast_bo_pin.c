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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_4__ {int num_placement; } ;
struct ast_bo {int pin_count; TYPE_2__ placement; int /*<<< orphan*/  bo; TYPE_1__* placements; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  ast_bo_gpu_offset (struct ast_bo*) ; 
 int /*<<< orphan*/  ast_ttm_placement (struct ast_bo*,int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,TYPE_2__*,struct ttm_operation_ctx*) ; 

int ast_bo_pin(struct ast_bo *bo, u32 pl_flag, u64 *gpu_addr)
{
	struct ttm_operation_ctx ctx = { false, false };
	int i, ret;

	if (bo->pin_count) {
		bo->pin_count++;
		if (gpu_addr)
			*gpu_addr = ast_bo_gpu_offset(bo);
	}

	ast_ttm_placement(bo, pl_flag);
	for (i = 0; i < bo->placement.num_placement; i++)
		bo->placements[i].flags |= TTM_PL_FLAG_NO_EVICT;
	ret = ttm_bo_validate(&bo->bo, &bo->placement, &ctx);
	if (ret)
		return ret;

	bo->pin_count = 1;
	if (gpu_addr)
		*gpu_addr = ast_bo_gpu_offset(bo);
	return 0;
}