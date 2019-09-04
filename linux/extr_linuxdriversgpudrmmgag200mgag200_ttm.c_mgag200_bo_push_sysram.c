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
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_5__ {int num_placement; } ;
struct TYPE_6__ {scalar_t__ virtual; } ;
struct mgag200_bo {TYPE_2__ placement; int /*<<< orphan*/  bo; TYPE_1__* placements; TYPE_3__ kmap; scalar_t__ pin_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 int /*<<< orphan*/  mgag200_ttm_placement (struct mgag200_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (TYPE_3__*) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,TYPE_2__*,struct ttm_operation_ctx*) ; 

int mgag200_bo_push_sysram(struct mgag200_bo *bo)
{
	struct ttm_operation_ctx ctx = { false, false };
	int i, ret;
	if (!bo->pin_count) {
		DRM_ERROR("unpin bad %p\n", bo);
		return 0;
	}
	bo->pin_count--;
	if (bo->pin_count)
		return 0;

	if (bo->kmap.virtual)
		ttm_bo_kunmap(&bo->kmap);

	mgag200_ttm_placement(bo, TTM_PL_FLAG_SYSTEM);
	for (i = 0; i < bo->placement.num_placement ; i++)
		bo->placements[i].flags |= TTM_PL_FLAG_NO_EVICT;

	ret = ttm_bo_validate(&bo->bo, &bo->placement, &ctx);
	if (ret) {
		DRM_ERROR("pushing to VRAM failed\n");
		return ret;
	}
	return 0;
}