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
struct vmw_user_resource_conv {int dummy; } ;
struct vmw_sw_context {struct vmw_resource* error_resource; TYPE_1__* fp; int /*<<< orphan*/  buf_start; int /*<<< orphan*/  res_relocations; struct vmw_res_cache_entry* res_cache; } ;
struct vmw_resource_val_node {int first_usage; } ;
struct vmw_resource {int dummy; } ;
struct vmw_res_cache_entry {int valid; scalar_t__ handle; struct vmw_resource_val_node* node; struct vmw_resource* res; } ;
struct vmw_private {int dummy; } ;
typedef  enum vmw_res_type { ____Placeholder_vmw_res_type } vmw_res_type ;
struct TYPE_2__ {int /*<<< orphan*/  tfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 scalar_t__ SVGA3D_INVALID_ID ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_cmd_res_reloc_add (struct vmw_private*,struct vmw_sw_context*,scalar_t__*,struct vmw_resource*,struct vmw_resource_val_node**) ; 
 int /*<<< orphan*/  vmw_ptr_diff (int /*<<< orphan*/ ,scalar_t__*) ; 
 int vmw_res_context ; 
 int /*<<< orphan*/  vmw_res_rel_normal ; 
 int vmw_resource_relocation_add (int /*<<< orphan*/ *,struct vmw_resource const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 int vmw_user_resource_lookup_handle (struct vmw_private*,int /*<<< orphan*/ ,scalar_t__,struct vmw_user_resource_conv const*,struct vmw_resource**) ; 

__attribute__((used)) static int
vmw_cmd_res_check(struct vmw_private *dev_priv,
		  struct vmw_sw_context *sw_context,
		  enum vmw_res_type res_type,
		  const struct vmw_user_resource_conv *converter,
		  uint32_t *id_loc,
		  struct vmw_resource_val_node **p_val)
{
	struct vmw_res_cache_entry *rcache =
		&sw_context->res_cache[res_type];
	struct vmw_resource *res;
	struct vmw_resource_val_node *node;
	int ret;

	if (*id_loc == SVGA3D_INVALID_ID) {
		if (p_val)
			*p_val = NULL;
		if (res_type == vmw_res_context) {
			DRM_ERROR("Illegal context invalid id.\n");
			return -EINVAL;
		}
		return 0;
	}

	/*
	 * Fastpath in case of repeated commands referencing the same
	 * resource
	 */

	if (likely(rcache->valid && *id_loc == rcache->handle)) {
		const struct vmw_resource *res = rcache->res;

		rcache->node->first_usage = false;
		if (p_val)
			*p_val = rcache->node;

		return vmw_resource_relocation_add
			(&sw_context->res_relocations, res,
			 vmw_ptr_diff(sw_context->buf_start, id_loc),
			 vmw_res_rel_normal);
	}

	ret = vmw_user_resource_lookup_handle(dev_priv,
					      sw_context->fp->tfile,
					      *id_loc,
					      converter,
					      &res);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Could not find or use resource 0x%08x.\n",
			  (unsigned) *id_loc);
		dump_stack();
		return ret;
	}

	rcache->valid = true;
	rcache->res = res;
	rcache->handle = *id_loc;

	ret = vmw_cmd_res_reloc_add(dev_priv, sw_context, id_loc,
				    res, &node);
	if (unlikely(ret != 0))
		goto out_no_reloc;

	rcache->node = node;
	if (p_val)
		*p_val = node;
	vmw_resource_unreference(&res);
	return 0;

out_no_reloc:
	BUG_ON(sw_context->error_resource != NULL);
	sw_context->error_resource = res;

	return ret;
}