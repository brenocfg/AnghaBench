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
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_4__ {int num_placement; } ;
struct drm_gem_vram_object {int /*<<< orphan*/  bo; scalar_t__ pin_count; TYPE_2__ placement; TYPE_1__* placements; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  drm_gem_vram_placement (struct drm_gem_vram_object*,unsigned long) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,TYPE_2__*,struct ttm_operation_ctx*) ; 

int drm_gem_vram_pin(struct drm_gem_vram_object *gbo, unsigned long pl_flag)
{
	int i, ret;
	struct ttm_operation_ctx ctx = { false, false };

	ret = ttm_bo_reserve(&gbo->bo, true, false, NULL);
	if (ret < 0)
		return ret;

	if (gbo->pin_count)
		goto out;

	if (pl_flag)
		drm_gem_vram_placement(gbo, pl_flag);

	for (i = 0; i < gbo->placement.num_placement; ++i)
		gbo->placements[i].flags |= TTM_PL_FLAG_NO_EVICT;

	ret = ttm_bo_validate(&gbo->bo, &gbo->placement, &ctx);
	if (ret < 0)
		goto err_ttm_bo_unreserve;

out:
	++gbo->pin_count;
	ttm_bo_unreserve(&gbo->bo);

	return 0;

err_ttm_bo_unreserve:
	ttm_bo_unreserve(&gbo->bo);
	return ret;
}