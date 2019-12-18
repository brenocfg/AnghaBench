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
struct vmw_resource {scalar_t__ pin_count; TYPE_1__* func; struct vmw_buffer_object* backup; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  reservation_sem; int /*<<< orphan*/  cmdbuf_mutex; } ;
struct vmw_buffer_object {int /*<<< orphan*/  base; int /*<<< orphan*/  pin_count; } ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_2__ {int /*<<< orphan*/  backup_placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_write_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_write_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_pin_reserved (struct vmw_buffer_object*,int) ; 
 int vmw_resource_reserve (struct vmw_resource*,int,int) ; 
 int /*<<< orphan*/  vmw_resource_unreserve (struct vmw_resource*,int,int,int,int /*<<< orphan*/ *,unsigned long) ; 
 int vmw_resource_validate (struct vmw_resource*,int) ; 

int vmw_resource_pin(struct vmw_resource *res, bool interruptible)
{
	struct ttm_operation_ctx ctx = { interruptible, false };
	struct vmw_private *dev_priv = res->dev_priv;
	int ret;

	ttm_write_lock(&dev_priv->reservation_sem, interruptible);
	mutex_lock(&dev_priv->cmdbuf_mutex);
	ret = vmw_resource_reserve(res, interruptible, false);
	if (ret)
		goto out_no_reserve;

	if (res->pin_count == 0) {
		struct vmw_buffer_object *vbo = NULL;

		if (res->backup) {
			vbo = res->backup;

			ttm_bo_reserve(&vbo->base, interruptible, false, NULL);
			if (!vbo->pin_count) {
				ret = ttm_bo_validate
					(&vbo->base,
					 res->func->backup_placement,
					 &ctx);
				if (ret) {
					ttm_bo_unreserve(&vbo->base);
					goto out_no_validate;
				}
			}

			/* Do we really need to pin the MOB as well? */
			vmw_bo_pin_reserved(vbo, true);
		}
		ret = vmw_resource_validate(res, interruptible);
		if (vbo)
			ttm_bo_unreserve(&vbo->base);
		if (ret)
			goto out_no_validate;
	}
	res->pin_count++;

out_no_validate:
	vmw_resource_unreserve(res, false, false, false, NULL, 0UL);
out_no_reserve:
	mutex_unlock(&dev_priv->cmdbuf_mutex);
	ttm_write_unlock(&dev_priv->reservation_sem);

	return ret;
}