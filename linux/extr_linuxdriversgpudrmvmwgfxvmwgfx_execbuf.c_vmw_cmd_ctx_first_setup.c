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
struct vmw_sw_context {int staged_bindings_inuse; int /*<<< orphan*/ * staged_bindings; } ;
struct vmw_resource_val_node {int /*<<< orphan*/ * staged_bindings; int /*<<< orphan*/  res; } ;
struct vmw_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 void* vmw_binding_state_alloc (struct vmw_private*) ; 
 int vmw_resource_context_res_add (struct vmw_private*,struct vmw_sw_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_cmd_ctx_first_setup(struct vmw_private *dev_priv,
				   struct vmw_sw_context *sw_context,
				   struct vmw_resource_val_node *node)
{
	int ret;

	ret = vmw_resource_context_res_add(dev_priv, sw_context, node->res);
	if (unlikely(ret != 0))
		goto out_err;

	if (!sw_context->staged_bindings) {
		sw_context->staged_bindings =
			vmw_binding_state_alloc(dev_priv);
		if (IS_ERR(sw_context->staged_bindings)) {
			DRM_ERROR("Failed to allocate context binding "
				  "information.\n");
			ret = PTR_ERR(sw_context->staged_bindings);
			sw_context->staged_bindings = NULL;
			goto out_err;
		}
	}

	if (sw_context->staged_bindings_inuse) {
		node->staged_bindings = vmw_binding_state_alloc(dev_priv);
		if (IS_ERR(node->staged_bindings)) {
			DRM_ERROR("Failed to allocate context binding "
				  "information.\n");
			ret = PTR_ERR(node->staged_bindings);
			node->staged_bindings = NULL;
			goto out_err;
		}
	} else {
		node->staged_bindings = sw_context->staged_bindings;
		sw_context->staged_bindings_inuse = true;
	}

	return 0;
out_err:
	return ret;
}