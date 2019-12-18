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
struct vmw_private {int /*<<< orphan*/  cman; } ;
struct vmw_cmdbuf_header {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA3D_INVALID_ID ; 
 int /*<<< orphan*/  vmw_apply_relocations (struct vmw_sw_context*) ; 
 int /*<<< orphan*/  vmw_cmdbuf_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmw_cmdbuf_header*,int) ; 
 void* vmw_cmdbuf_reserve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct vmw_cmdbuf_header*) ; 
 int /*<<< orphan*/  vmw_resource_relocations_apply (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_resource_relocations_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmw_execbuf_submit_cmdbuf(struct vmw_private *dev_priv,
				     struct vmw_cmdbuf_header *header,
				     u32 command_size,
				     struct vmw_sw_context *sw_context)
{
	u32 id = ((sw_context->dx_ctx_node) ? sw_context->dx_ctx_node->ctx->id :
		  SVGA3D_INVALID_ID);
	void *cmd = vmw_cmdbuf_reserve(dev_priv->cman, command_size, id, false,
				       header);

	vmw_apply_relocations(sw_context);
	vmw_resource_relocations_apply(cmd, &sw_context->res_relocations);
	vmw_resource_relocations_free(&sw_context->res_relocations);
	vmw_cmdbuf_commit(dev_priv->cman, command_size, header, false);

	return 0;
}