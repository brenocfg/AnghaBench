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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_sw_context {int /*<<< orphan*/  man; struct vmw_resource_val_node* dx_ctx_node; } ;
struct vmw_resource_val_node {int dummy; } ;
struct vmw_resource {int dummy; } ;
typedef  enum vmw_view_type { ____Placeholder_vmw_view_type } vmw_view_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct vmw_resource*) ; 
 int PTR_ERR (struct vmw_resource*) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 struct vmw_resource* vmw_view_lookup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int vmw_view_res_val_add (struct vmw_sw_context*,struct vmw_resource*) ; 

__attribute__((used)) static int vmw_view_id_val_add(struct vmw_sw_context *sw_context,
			       enum vmw_view_type view_type, u32 id)
{
	struct vmw_resource_val_node *ctx_node = sw_context->dx_ctx_node;
	struct vmw_resource *view;
	int ret;

	if (!ctx_node) {
		DRM_ERROR("DX Context not set.\n");
		return -EINVAL;
	}

	view = vmw_view_lookup(sw_context->man, view_type, id);
	if (IS_ERR(view))
		return PTR_ERR(view);

	ret = vmw_view_res_val_add(sw_context, view);
	vmw_resource_unreference(&view);

	return ret;
}