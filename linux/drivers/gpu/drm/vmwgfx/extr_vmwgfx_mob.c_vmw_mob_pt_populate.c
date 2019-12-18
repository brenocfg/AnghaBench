#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vmw_private {int /*<<< orphan*/  bdev; } ;
struct vmw_mob {int num_pages; TYPE_1__* pt_bo; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct TYPE_8__ {int (* ttm_tt_populate ) (int /*<<< orphan*/ ,struct ttm_operation_ctx*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  ttm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SIZE ; 
 int stub1 (int /*<<< orphan*/ ,struct ttm_operation_ctx*) ; 
 int ttm_bo_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int /*<<< orphan*/  ttm_bo_put (TYPE_1__*) ; 
 int ttm_bo_reserve (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 
 int /*<<< orphan*/  ttm_bo_unreserve (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_2__ vmw_bo_driver ; 
 int vmw_bo_map_dma (TYPE_1__*) ; 
 int /*<<< orphan*/  vmw_sys_ne_placement ; 

__attribute__((used)) static int vmw_mob_pt_populate(struct vmw_private *dev_priv,
			       struct vmw_mob *mob)
{
	int ret;
	struct ttm_operation_ctx ctx = {
		.interruptible = false,
		.no_wait_gpu = false
	};

	BUG_ON(mob->pt_bo != NULL);

	ret = ttm_bo_create(&dev_priv->bdev, mob->num_pages * PAGE_SIZE,
			    ttm_bo_type_device,
			    &vmw_sys_ne_placement,
			    0, false, &mob->pt_bo);
	if (unlikely(ret != 0))
		return ret;

	ret = ttm_bo_reserve(mob->pt_bo, false, true, NULL);

	BUG_ON(ret != 0);
	ret = vmw_bo_driver.ttm_tt_populate(mob->pt_bo->ttm, &ctx);
	if (unlikely(ret != 0))
		goto out_unreserve;
	ret = vmw_bo_map_dma(mob->pt_bo);
	if (unlikely(ret != 0))
		goto out_unreserve;

	ttm_bo_unreserve(mob->pt_bo);

	return 0;

out_unreserve:
	ttm_bo_unreserve(mob->pt_bo);
	ttm_bo_put(mob->pt_bo);
	mob->pt_bo = NULL;

	return ret;
}