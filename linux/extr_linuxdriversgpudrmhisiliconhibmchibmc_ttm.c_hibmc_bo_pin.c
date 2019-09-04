#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int num_placement; } ;
struct hibmc_bo {int pin_count; TYPE_2__ bo; TYPE_3__ placement; TYPE_1__* placements; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  hibmc_ttm_placement (struct hibmc_bo*,int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (TYPE_2__*,TYPE_3__*,struct ttm_operation_ctx*) ; 

int hibmc_bo_pin(struct hibmc_bo *bo, u32 pl_flag, u64 *gpu_addr)
{
	struct ttm_operation_ctx ctx = { false, false };
	int i, ret;

	if (bo->pin_count) {
		bo->pin_count++;
		if (gpu_addr)
			*gpu_addr = bo->bo.offset;
		return 0;
	}

	hibmc_ttm_placement(bo, pl_flag);
	for (i = 0; i < bo->placement.num_placement; i++)
		bo->placements[i].flags |= TTM_PL_FLAG_NO_EVICT;
	ret = ttm_bo_validate(&bo->bo, &bo->placement, &ctx);
	if (ret)
		return ret;

	bo->pin_count = 1;
	if (gpu_addr)
		*gpu_addr = bo->bo.offset;
	return 0;
}