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
struct vmw_user_resource_conv {int dummy; } ;
struct vmw_sw_context {int dummy; } ;
struct vmw_resource {int dummy; } ;
struct vmw_private {int dummy; } ;
typedef  enum vmw_res_type { ____Placeholder_vmw_res_type } vmw_res_type ;

/* Variables and functions */
 int /*<<< orphan*/  VMW_RES_DIRTY_NONE ; 
 int vmw_cmd_res_check (struct vmw_private*,struct vmw_sw_context*,int,int /*<<< orphan*/ ,struct vmw_user_resource_conv const*,int /*<<< orphan*/ *,struct vmw_resource**) ; 
 int vmw_cmd_res_switch_backup (struct vmw_private*,struct vmw_sw_context*,struct vmw_resource*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int vmw_cmd_switch_backup(struct vmw_private *dev_priv,
				 struct vmw_sw_context *sw_context,
				 enum vmw_res_type res_type,
				 const struct vmw_user_resource_conv
				 *converter, uint32_t *res_id, uint32_t *buf_id,
				 unsigned long backup_offset)
{
	struct vmw_resource *res;
	int ret;

	ret = vmw_cmd_res_check(dev_priv, sw_context, res_type,
				VMW_RES_DIRTY_NONE, converter, res_id, &res);
	if (ret)
		return ret;

	return vmw_cmd_res_switch_backup(dev_priv, sw_context, res, buf_id,
					 backup_offset);
}