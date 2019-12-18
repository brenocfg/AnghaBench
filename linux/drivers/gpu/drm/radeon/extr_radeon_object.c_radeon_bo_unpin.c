#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_7__ {scalar_t__ mem_type; } ;
struct TYPE_9__ {TYPE_2__ mem; } ;
struct TYPE_10__ {int num_placement; } ;
struct radeon_bo {TYPE_3__* rdev; TYPE_4__ tbo; TYPE_5__ placement; TYPE_1__* placements; scalar_t__ pin_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  gart_pin_size; int /*<<< orphan*/  vram_pin_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; scalar_t__ lpfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct radeon_bo*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,struct radeon_bo*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ radeon_bo_size (struct radeon_bo*) ; 
 int ttm_bo_validate (TYPE_4__*,TYPE_5__*,struct ttm_operation_ctx*) ; 

int radeon_bo_unpin(struct radeon_bo *bo)
{
	struct ttm_operation_ctx ctx = { false, false };
	int r, i;

	if (!bo->pin_count) {
		dev_warn(bo->rdev->dev, "%p unpin not necessary\n", bo);
		return 0;
	}
	bo->pin_count--;
	if (bo->pin_count)
		return 0;
	for (i = 0; i < bo->placement.num_placement; i++) {
		bo->placements[i].lpfn = 0;
		bo->placements[i].flags &= ~TTM_PL_FLAG_NO_EVICT;
	}
	r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	if (likely(r == 0)) {
		if (bo->tbo.mem.mem_type == TTM_PL_VRAM)
			bo->rdev->vram_pin_size -= radeon_bo_size(bo);
		else
			bo->rdev->gart_pin_size -= radeon_bo_size(bo);
	} else {
		dev_err(bo->rdev->dev, "%p validate failed for unpin\n", bo);
	}
	return r;
}