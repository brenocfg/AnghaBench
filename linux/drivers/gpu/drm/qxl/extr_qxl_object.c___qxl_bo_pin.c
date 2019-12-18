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
struct TYPE_3__ {struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct qxl_bo {int pin_count; int /*<<< orphan*/  placement; TYPE_2__ tbo; int /*<<< orphan*/  type; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct qxl_bo*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  qxl_ttm_placement_from_domain (struct qxl_bo*,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_validate (TYPE_2__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __qxl_bo_pin(struct qxl_bo *bo)
{
	struct ttm_operation_ctx ctx = { false, false };
	struct drm_device *ddev = bo->tbo.base.dev;
	int r;

	if (bo->pin_count) {
		bo->pin_count++;
		return 0;
	}
	qxl_ttm_placement_from_domain(bo, bo->type, true);
	r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	if (likely(r == 0)) {
		bo->pin_count = 1;
	}
	if (unlikely(r != 0))
		dev_err(ddev->dev, "%p pin failed\n", bo);
	return r;
}