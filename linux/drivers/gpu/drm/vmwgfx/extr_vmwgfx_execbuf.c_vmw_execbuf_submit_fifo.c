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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_sw_context {int /*<<< orphan*/  res_relocations; TYPE_2__* dx_ctx_node; } ;
struct vmw_private {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* VMW_FIFO_RESERVE (struct vmw_private*,int /*<<< orphan*/ ) ; 
 void* VMW_FIFO_RESERVE_DX (struct vmw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_apply_relocations (struct vmw_sw_context*) ; 
 int /*<<< orphan*/  vmw_fifo_commit (struct vmw_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_resource_relocations_apply (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_resource_relocations_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmw_execbuf_submit_fifo(struct vmw_private *dev_priv,
				   void *kernel_commands, u32 command_size,
				   struct vmw_sw_context *sw_context)
{
	void *cmd;

	if (sw_context->dx_ctx_node)
		cmd = VMW_FIFO_RESERVE_DX(dev_priv, command_size,
					  sw_context->dx_ctx_node->ctx->id);
	else
		cmd = VMW_FIFO_RESERVE(dev_priv, command_size);

	if (!cmd)
		return -ENOMEM;

	vmw_apply_relocations(sw_context);
	memcpy(cmd, kernel_commands, command_size);
	vmw_resource_relocations_apply(cmd, &sw_context->res_relocations);
	vmw_resource_relocations_free(&sw_context->res_relocations);
	vmw_fifo_commit(dev_priv, command_size);

	return 0;
}