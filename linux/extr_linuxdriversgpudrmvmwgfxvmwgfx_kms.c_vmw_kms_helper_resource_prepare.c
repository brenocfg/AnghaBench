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
struct vmw_validation_ctx {int /*<<< orphan*/ * buf; struct vmw_resource* res; } ;
struct vmw_resource {TYPE_1__* dev_priv; scalar_t__ backup; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmdbuf_mutex; int /*<<< orphan*/  has_mob; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * vmw_bo_reference (scalar_t__) ; 
 int vmw_kms_helper_buffer_prepare (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmw_kms_helper_buffer_revert (int /*<<< orphan*/ *) ; 
 int vmw_resource_reserve (struct vmw_resource*,int,int) ; 
 int /*<<< orphan*/  vmw_resource_unreserve (struct vmw_resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vmw_resource_validate (struct vmw_resource*) ; 

int vmw_kms_helper_resource_prepare(struct vmw_resource *res,
				    bool interruptible,
				    struct vmw_validation_ctx *ctx)
{
	int ret = 0;

	ctx->buf = NULL;
	ctx->res = res;

	if (interruptible)
		ret = mutex_lock_interruptible(&res->dev_priv->cmdbuf_mutex);
	else
		mutex_lock(&res->dev_priv->cmdbuf_mutex);

	if (unlikely(ret != 0))
		return -ERESTARTSYS;

	ret = vmw_resource_reserve(res, interruptible, false);
	if (ret)
		goto out_unlock;

	if (res->backup) {
		ret = vmw_kms_helper_buffer_prepare(res->dev_priv, res->backup,
						    interruptible,
						    res->dev_priv->has_mob,
						    false);
		if (ret)
			goto out_unreserve;

		ctx->buf = vmw_bo_reference(res->backup);
	}
	ret = vmw_resource_validate(res);
	if (ret)
		goto out_revert;
	return 0;

out_revert:
	vmw_kms_helper_buffer_revert(ctx->buf);
out_unreserve:
	vmw_resource_unreserve(res, false, NULL, 0);
out_unlock:
	mutex_unlock(&res->dev_priv->cmdbuf_mutex);
	return ret;
}