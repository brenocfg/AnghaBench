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
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct qxl_bo {TYPE_2__ gem_base; TYPE_3__ tbo; int /*<<< orphan*/  placement; int /*<<< orphan*/  type; int /*<<< orphan*/  pin_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_private; } ;

/* Variables and functions */
 int qxl_bo_check_id (int /*<<< orphan*/ ,struct qxl_bo*) ; 
 int /*<<< orphan*/  qxl_ttm_placement_from_domain (struct qxl_bo*,int /*<<< orphan*/ ,int) ; 
 int reservation_object_reserve_shared (int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (TYPE_3__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 

__attribute__((used)) static int qxl_release_validate_bo(struct qxl_bo *bo)
{
	struct ttm_operation_ctx ctx = { true, false };
	int ret;

	if (!bo->pin_count) {
		qxl_ttm_placement_from_domain(bo, bo->type, false);
		ret = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
		if (ret)
			return ret;
	}

	ret = reservation_object_reserve_shared(bo->tbo.resv);
	if (ret)
		return ret;

	/* allocate a surface for reserved + validated buffers */
	ret = qxl_bo_check_id(bo->gem_base.dev->dev_private, bo);
	if (ret)
		return ret;
	return 0;
}