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
struct vmw_resource {scalar_t__ pin_count; struct vmw_buffer_object* backup; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  reservation_sem; int /*<<< orphan*/  cmdbuf_mutex; } ;
struct vmw_buffer_object {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (struct vmw_buffer_object*,int) ; 
 int vmw_resource_reserve (struct vmw_resource*,int,int) ; 
 int /*<<< orphan*/  vmw_resource_unreserve (struct vmw_resource*,int,int,int,int /*<<< orphan*/ *,unsigned long) ; 

void vmw_resource_unpin(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;
	int ret;

	(void) ttm_read_lock(&dev_priv->reservation_sem, false);
	mutex_lock(&dev_priv->cmdbuf_mutex);

	ret = vmw_resource_reserve(res, false, true);
	WARN_ON(ret);

	WARN_ON(res->pin_count == 0);
	if (--res->pin_count == 0 && res->backup) {
		struct vmw_buffer_object *vbo = res->backup;

		(void) ttm_bo_reserve(&vbo->base, false, false, NULL);
		vmw_bo_pin_reserved(vbo, false);
		ttm_bo_unreserve(&vbo->base);
	}

	vmw_resource_unreserve(res, false, false, false, NULL, 0UL);

	mutex_unlock(&dev_priv->cmdbuf_mutex);
	ttm_read_unlock(&dev_priv->reservation_sem);
}