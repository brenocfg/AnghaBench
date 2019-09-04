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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_sw_context {int /*<<< orphan*/  buf_start; int /*<<< orphan*/  res_relocations; } ;
struct vmw_resource_val_node {int dummy; } ;
struct vmw_resource {int dummy; } ;
struct vmw_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_ptr_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_res_rel_normal ; 
 int vmw_resource_relocation_add (int /*<<< orphan*/ *,struct vmw_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmw_resource_val_add (struct vmw_sw_context*,struct vmw_resource*,struct vmw_resource_val_node**) ; 

__attribute__((used)) static int vmw_cmd_res_reloc_add(struct vmw_private *dev_priv,
				 struct vmw_sw_context *sw_context,
				 uint32_t *id_loc,
				 struct vmw_resource *res,
				 struct vmw_resource_val_node **p_val)
{
	int ret;
	struct vmw_resource_val_node *node;

	*p_val = NULL;
	ret = vmw_resource_relocation_add(&sw_context->res_relocations,
					  res,
					  vmw_ptr_diff(sw_context->buf_start,
						       id_loc),
					  vmw_res_rel_normal);
	if (unlikely(ret != 0))
		return ret;

	ret = vmw_resource_val_add(sw_context, res, &node);
	if (unlikely(ret != 0))
		return ret;

	if (p_val)
		*p_val = node;

	return 0;
}