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
typedef  scalar_t__ uint32_t ;
struct vmw_sw_context {int /*<<< orphan*/  man; struct vmw_resource_val_node* dx_ctx_node; TYPE_1__* fp; } ;
struct vmw_resource_val_node {int dummy; } ;
struct vmw_resource {int dummy; } ;
struct vmw_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 scalar_t__ SVGA3D_INVALID_ID ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  user_context_converter ; 
 int /*<<< orphan*/  vmw_context_res_man (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 int vmw_resource_val_add (struct vmw_sw_context*,struct vmw_resource*,struct vmw_resource_val_node**) ; 
 int vmw_user_resource_lookup_handle (struct vmw_private*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct vmw_resource**) ; 

__attribute__((used)) static int vmw_execbuf_tie_context(struct vmw_private *dev_priv,
				   struct vmw_sw_context *sw_context,
				   uint32_t handle)
{
	struct vmw_resource_val_node *ctx_node;
	struct vmw_resource *res;
	int ret;

	if (handle == SVGA3D_INVALID_ID)
		return 0;

	ret = vmw_user_resource_lookup_handle(dev_priv, sw_context->fp->tfile,
					      handle, user_context_converter,
					      &res);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Could not find or user DX context 0x%08x.\n",
			  (unsigned) handle);
		return ret;
	}

	ret = vmw_resource_val_add(sw_context, res, &ctx_node);
	if (unlikely(ret != 0))
		goto out_err;

	sw_context->dx_ctx_node = ctx_node;
	sw_context->man = vmw_context_res_man(res);
out_err:
	vmw_resource_unreference(&res);
	return ret;
}