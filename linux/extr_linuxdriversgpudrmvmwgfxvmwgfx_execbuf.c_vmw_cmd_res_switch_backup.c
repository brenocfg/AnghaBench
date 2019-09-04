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
struct vmw_sw_context {int dummy; } ;
struct vmw_resource_val_node {int switching_backup; int no_buffer_needed; unsigned long new_backup_offset; struct vmw_buffer_object* new_backup; scalar_t__ first_usage; } ;
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 int vmw_translate_mob_ptr (struct vmw_private*,struct vmw_sw_context*,int /*<<< orphan*/ *,struct vmw_buffer_object**) ; 

__attribute__((used)) static int vmw_cmd_res_switch_backup(struct vmw_private *dev_priv,
				     struct vmw_sw_context *sw_context,
				     struct vmw_resource_val_node *val_node,
				     uint32_t *buf_id,
				     unsigned long backup_offset)
{
	struct vmw_buffer_object *dma_buf;
	int ret;

	ret = vmw_translate_mob_ptr(dev_priv, sw_context, buf_id, &dma_buf);
	if (ret)
		return ret;

	val_node->switching_backup = true;
	if (val_node->first_usage)
		val_node->no_buffer_needed = true;

	vmw_bo_unreference(&val_node->new_backup);
	val_node->new_backup = dma_buf;
	val_node->new_backup_offset = backup_offset;

	return 0;
}