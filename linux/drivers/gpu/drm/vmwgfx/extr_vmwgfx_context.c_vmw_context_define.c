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
struct TYPE_4__ {int shareable; int /*<<< orphan*/  handle; int /*<<< orphan*/ * tfile; } ;
struct vmw_resource {int dummy; } ;
struct vmw_user_context {TYPE_2__ base; struct vmw_resource res; } ;
struct vmw_private {int /*<<< orphan*/  reservation_sem; scalar_t__ has_mob; int /*<<< orphan*/  has_dx; } ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; } ;
struct ttm_object_file {int dummy; } ;
struct drm_vmw_context_arg {int /*<<< orphan*/  cid; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {struct ttm_object_file* tfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TTM_OBJ_EXTRA_SIZE ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*) ; 
 int /*<<< orphan*/  VMW_IDA_ACC_SIZE ; 
 int /*<<< orphan*/  VMW_RES_CONTEXT ; 
 struct vmw_user_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ttm_base_object_init (struct ttm_object_file*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ttm_mem_global_alloc (int /*<<< orphan*/ ,scalar_t__,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int ttm_read_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_read_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ttm_round_pot (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_cmdbuf_res_man_size () ; 
 int vmw_context_init (struct vmw_private*,struct vmw_resource*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* vmw_fpriv (struct drm_file*) ; 
 int /*<<< orphan*/  vmw_mem_glob (struct vmw_private*) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 
 struct vmw_resource* vmw_resource_reference (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 int /*<<< orphan*/  vmw_user_context_base_release ; 
 int /*<<< orphan*/  vmw_user_context_free ; 
 scalar_t__ vmw_user_context_size ; 

__attribute__((used)) static int vmw_context_define(struct drm_device *dev, void *data,
			      struct drm_file *file_priv, bool dx)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	struct vmw_user_context *ctx;
	struct vmw_resource *res;
	struct vmw_resource *tmp;
	struct drm_vmw_context_arg *arg = (struct drm_vmw_context_arg *)data;
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	struct ttm_operation_ctx ttm_opt_ctx = {
		.interruptible = true,
		.no_wait_gpu = false
	};
	int ret;

	if (!dev_priv->has_dx && dx) {
		VMW_DEBUG_USER("DX contexts not supported by device.\n");
		return -EINVAL;
	}

	if (unlikely(vmw_user_context_size == 0))
		vmw_user_context_size = ttm_round_pot(sizeof(*ctx)) +
		  ((dev_priv->has_mob) ? vmw_cmdbuf_res_man_size() : 0) +
		  + VMW_IDA_ACC_SIZE + TTM_OBJ_EXTRA_SIZE;

	ret = ttm_read_lock(&dev_priv->reservation_sem, true);
	if (unlikely(ret != 0))
		return ret;

	ret = ttm_mem_global_alloc(vmw_mem_glob(dev_priv),
				   vmw_user_context_size,
				   &ttm_opt_ctx);
	if (unlikely(ret != 0)) {
		if (ret != -ERESTARTSYS)
			DRM_ERROR("Out of graphics memory for context"
				  " creation.\n");
		goto out_unlock;
	}

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (unlikely(!ctx)) {
		ttm_mem_global_free(vmw_mem_glob(dev_priv),
				    vmw_user_context_size);
		ret = -ENOMEM;
		goto out_unlock;
	}

	res = &ctx->res;
	ctx->base.shareable = false;
	ctx->base.tfile = NULL;

	/*
	 * From here on, the destructor takes over resource freeing.
	 */

	ret = vmw_context_init(dev_priv, res, vmw_user_context_free, dx);
	if (unlikely(ret != 0))
		goto out_unlock;

	tmp = vmw_resource_reference(&ctx->res);
	ret = ttm_base_object_init(tfile, &ctx->base, false, VMW_RES_CONTEXT,
				   &vmw_user_context_base_release, NULL);

	if (unlikely(ret != 0)) {
		vmw_resource_unreference(&tmp);
		goto out_err;
	}

	arg->cid = ctx->base.handle;
out_err:
	vmw_resource_unreference(&res);
out_unlock:
	ttm_read_unlock(&dev_priv->reservation_sem);
	return ret;
}