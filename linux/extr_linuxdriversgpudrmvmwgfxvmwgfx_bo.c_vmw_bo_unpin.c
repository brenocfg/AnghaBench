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
struct vmw_private {int /*<<< orphan*/  reservation_sem; } ;
struct ttm_buffer_object {int dummy; } ;
struct vmw_buffer_object {struct ttm_buffer_object base; } ;

/* Variables and functions */
 int ttm_bo_reserve (struct ttm_buffer_object*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (struct vmw_buffer_object*,int) ; 

int vmw_bo_unpin(struct vmw_private *dev_priv,
		 struct vmw_buffer_object *buf,
		 bool interruptible)
{
	struct ttm_buffer_object *bo = &buf->base;
	int ret;

	ret = ttm_read_lock(&dev_priv->reservation_sem, interruptible);
	if (unlikely(ret != 0))
		return ret;

	ret = ttm_bo_reserve(bo, interruptible, false, NULL);
	if (unlikely(ret != 0))
		goto err;

	vmw_bo_pin_reserved(buf, false);

	ttm_bo_unreserve(bo);

err:
	ttm_read_unlock(&dev_priv->reservation_sem);
	return ret;
}