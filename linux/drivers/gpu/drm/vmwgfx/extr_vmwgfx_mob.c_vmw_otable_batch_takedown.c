#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmw_private {int dummy; } ;
struct vmw_otable_batch {size_t num_otables; struct ttm_buffer_object* otable_bo; TYPE_1__* otables; } ;
struct ttm_buffer_object {int dummy; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;
typedef  size_t SVGAOTableType ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ttm_bo_put (struct ttm_buffer_object*) ; 
 int ttm_bo_reserve (struct ttm_buffer_object*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  vmw_bo_fence_single (struct ttm_buffer_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_takedown_otable_base (struct vmw_private*,size_t,TYPE_1__*) ; 

__attribute__((used)) static void vmw_otable_batch_takedown(struct vmw_private *dev_priv,
			       struct vmw_otable_batch *batch)
{
	SVGAOTableType i;
	struct ttm_buffer_object *bo = batch->otable_bo;
	int ret;

	for (i = 0; i < batch->num_otables; ++i)
		if (batch->otables[i].enabled)
			vmw_takedown_otable_base(dev_priv, i,
						 &batch->otables[i]);

	ret = ttm_bo_reserve(bo, false, true, NULL);
	BUG_ON(ret != 0);

	vmw_bo_fence_single(bo, NULL);
	ttm_bo_unreserve(bo);

	ttm_bo_put(batch->otable_bo);
	batch->otable_bo = NULL;
}