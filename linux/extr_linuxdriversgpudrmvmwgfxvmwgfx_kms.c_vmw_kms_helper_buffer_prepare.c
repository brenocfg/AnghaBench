#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vmw_private {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;
struct vmw_buffer_object {struct ttm_buffer_object base; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_reserve (struct ttm_buffer_object*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_bo_validate (struct ttm_buffer_object*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  vmw_nonfixed_placement ; 
 int vmw_validate_single_buffer (struct vmw_private*,struct ttm_buffer_object*,int,int) ; 

int vmw_kms_helper_buffer_prepare(struct vmw_private *dev_priv,
				  struct vmw_buffer_object *buf,
				  bool interruptible,
				  bool validate_as_mob,
				  bool for_cpu_blit)
{
	struct ttm_operation_ctx ctx = {
		.interruptible = interruptible,
		.no_wait_gpu = false};
	struct ttm_buffer_object *bo = &buf->base;
	int ret;

	ttm_bo_reserve(bo, false, false, NULL);
	if (for_cpu_blit)
		ret = ttm_bo_validate(bo, &vmw_nonfixed_placement, &ctx);
	else
		ret = vmw_validate_single_buffer(dev_priv, bo, interruptible,
						 validate_as_mob);
	if (ret)
		ttm_bo_unreserve(bo);

	return ret;
}