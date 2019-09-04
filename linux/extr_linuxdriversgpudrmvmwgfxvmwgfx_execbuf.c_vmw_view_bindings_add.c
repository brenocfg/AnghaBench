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
typedef  scalar_t__ uint32 ;
typedef  size_t u32 ;
struct vmw_sw_context {struct vmw_cmdbuf_res_manager* man; struct vmw_resource_val_node* dx_ctx_node; } ;
struct vmw_resource_val_node {int /*<<< orphan*/  staged_bindings; int /*<<< orphan*/  res; } ;
struct vmw_resource {int dummy; } ;
struct TYPE_2__ {int bt; struct vmw_resource* res; int /*<<< orphan*/  ctx; } ;
struct vmw_ctx_bindinfo_view {size_t slot; TYPE_1__ bi; scalar_t__ shader_slot; } ;
struct vmw_cmdbuf_res_manager {int dummy; } ;
typedef  enum vmw_view_type { ____Placeholder_vmw_view_type } vmw_view_type ;
typedef  enum vmw_ctx_binding_type { ____Placeholder_vmw_ctx_binding_type } vmw_ctx_binding_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct vmw_resource*) ; 
 int PTR_ERR (struct vmw_resource*) ; 
 scalar_t__ SVGA3D_INVALID_ID ; 
 int /*<<< orphan*/  vmw_binding_add (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 struct vmw_resource* vmw_view_lookup (struct vmw_cmdbuf_res_manager*,int,scalar_t__) ; 
 int vmw_view_res_val_add (struct vmw_sw_context*,struct vmw_resource*) ; 

__attribute__((used)) static int vmw_view_bindings_add(struct vmw_sw_context *sw_context,
				 enum vmw_view_type view_type,
				 enum vmw_ctx_binding_type binding_type,
				 uint32 shader_slot,
				 uint32 view_ids[], u32 num_views,
				 u32 first_slot)
{
	struct vmw_resource_val_node *ctx_node = sw_context->dx_ctx_node;
	struct vmw_cmdbuf_res_manager *man;
	u32 i;
	int ret;

	if (!ctx_node) {
		DRM_ERROR("DX Context not set.\n");
		return -EINVAL;
	}

	man = sw_context->man;
	for (i = 0; i < num_views; ++i) {
		struct vmw_ctx_bindinfo_view binding;
		struct vmw_resource *view = NULL;

		if (view_ids[i] != SVGA3D_INVALID_ID) {
			view = vmw_view_lookup(man, view_type, view_ids[i]);
			if (IS_ERR(view)) {
				DRM_ERROR("View not found.\n");
				return PTR_ERR(view);
			}

			ret = vmw_view_res_val_add(sw_context, view);
			if (ret) {
				DRM_ERROR("Could not add view to "
					  "validation list.\n");
				vmw_resource_unreference(&view);
				return ret;
			}
		}
		binding.bi.ctx = ctx_node->res;
		binding.bi.res = view;
		binding.bi.bt = binding_type;
		binding.shader_slot = shader_slot;
		binding.slot = first_slot + i;
		vmw_binding_add(ctx_node->staged_bindings, &binding.bi,
				shader_slot, binding.slot);
		if (view)
			vmw_resource_unreference(&view);
	}

	return 0;
}