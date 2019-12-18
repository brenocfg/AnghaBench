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
struct vmw_sw_context {int staged_bindings_inuse; int /*<<< orphan*/  ctx_list; int /*<<< orphan*/ * staged_bindings; } ;
struct vmw_resource {int dummy; } ;
struct vmw_private {int dummy; } ;
struct vmw_ctx_validation_info {int /*<<< orphan*/  head; int /*<<< orphan*/  cur; struct vmw_resource* ctx; int /*<<< orphan*/ * staged; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 void* vmw_binding_state_alloc (struct vmw_private*) ; 
 int /*<<< orphan*/  vmw_context_binding_state (struct vmw_resource*) ; 
 int vmw_resource_context_res_add (struct vmw_private*,struct vmw_sw_context*,struct vmw_resource*) ; 

__attribute__((used)) static int vmw_cmd_ctx_first_setup(struct vmw_private *dev_priv,
				   struct vmw_sw_context *sw_context,
				   struct vmw_resource *res,
				   struct vmw_ctx_validation_info *node)
{
	int ret;

	ret = vmw_resource_context_res_add(dev_priv, sw_context, res);
	if (unlikely(ret != 0))
		goto out_err;

	if (!sw_context->staged_bindings) {
		sw_context->staged_bindings = vmw_binding_state_alloc(dev_priv);
		if (IS_ERR(sw_context->staged_bindings)) {
			ret = PTR_ERR(sw_context->staged_bindings);
			sw_context->staged_bindings = NULL;
			goto out_err;
		}
	}

	if (sw_context->staged_bindings_inuse) {
		node->staged = vmw_binding_state_alloc(dev_priv);
		if (IS_ERR(node->staged)) {
			ret = PTR_ERR(node->staged);
			node->staged = NULL;
			goto out_err;
		}
	} else {
		node->staged = sw_context->staged_bindings;
		sw_context->staged_bindings_inuse = true;
	}

	node->ctx = res;
	node->cur = vmw_context_binding_state(res);
	list_add_tail(&node->head, &sw_context->ctx_list);

	return 0;

out_err:
	return ret;
}