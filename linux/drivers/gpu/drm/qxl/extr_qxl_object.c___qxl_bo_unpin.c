#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_8__ {int num_placement; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct qxl_bo {TYPE_4__ placement; TYPE_3__ tbo; TYPE_2__* placements; scalar_t__ pin_count; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct qxl_bo*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,struct qxl_bo*) ; 
 int ttm_bo_validate (TYPE_3__*,TYPE_4__*,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __qxl_bo_unpin(struct qxl_bo *bo)
{
	struct ttm_operation_ctx ctx = { false, false };
	struct drm_device *ddev = bo->tbo.base.dev;
	int r, i;

	if (!bo->pin_count) {
		dev_warn(ddev->dev, "%p unpin not necessary\n", bo);
		return 0;
	}
	bo->pin_count--;
	if (bo->pin_count)
		return 0;
	for (i = 0; i < bo->placement.num_placement; i++)
		bo->placements[i].flags &= ~TTM_PL_FLAG_NO_EVICT;
	r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	if (unlikely(r != 0))
		dev_err(ddev->dev, "%p validate failed for unpin\n", bo);
	return r;
}