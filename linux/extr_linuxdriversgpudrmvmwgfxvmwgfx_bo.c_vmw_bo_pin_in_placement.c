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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_private {int /*<<< orphan*/  reservation_sem; } ;
struct ttm_buffer_object {int /*<<< orphan*/  mem; } ;
struct vmw_buffer_object {scalar_t__ pin_count; struct ttm_buffer_object base; } ;
struct ttm_placement {int dummy; } ;
struct ttm_operation_ctx {int member_0; int member_1; } ;

/* Variables and functions */
 int EINVAL ; 
 int ttm_bo_mem_compat (struct ttm_placement*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ttm_bo_reserve (struct ttm_buffer_object*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_bo_validate (struct ttm_buffer_object*,struct ttm_placement*,struct ttm_operation_ctx*) ; 
 int ttm_write_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_write_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (struct vmw_buffer_object*,int) ; 
 int /*<<< orphan*/  vmw_execbuf_release_pinned_bo (struct vmw_private*) ; 

int vmw_bo_pin_in_placement(struct vmw_private *dev_priv,
			    struct vmw_buffer_object *buf,
			    struct ttm_placement *placement,
			    bool interruptible)
{
	struct ttm_operation_ctx ctx = {interruptible, false };
	struct ttm_buffer_object *bo = &buf->base;
	int ret;
	uint32_t new_flags;

	ret = ttm_write_lock(&dev_priv->reservation_sem, interruptible);
	if (unlikely(ret != 0))
		return ret;

	vmw_execbuf_release_pinned_bo(dev_priv);

	ret = ttm_bo_reserve(bo, interruptible, false, NULL);
	if (unlikely(ret != 0))
		goto err;

	if (buf->pin_count > 0)
		ret = ttm_bo_mem_compat(placement, &bo->mem,
					&new_flags) == true ? 0 : -EINVAL;
	else
		ret = ttm_bo_validate(bo, placement, &ctx);

	if (!ret)
		vmw_bo_pin_reserved(buf, true);

	ttm_bo_unreserve(bo);

err:
	ttm_write_unlock(&dev_priv->reservation_sem);
	return ret;
}