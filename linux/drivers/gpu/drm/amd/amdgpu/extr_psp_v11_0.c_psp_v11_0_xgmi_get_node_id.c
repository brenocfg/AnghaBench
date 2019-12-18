#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  node_id; } ;
struct TYPE_6__ {TYPE_2__ get_node_id; } ;
struct ta_xgmi_shared_memory {TYPE_3__ xgmi_out_message; int /*<<< orphan*/  cmd_id; } ;
struct TYPE_4__ {scalar_t__ xgmi_shared_buf; } ;
struct psp_context {TYPE_1__ xgmi_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_COMMAND_XGMI__GET_NODE_ID ; 
 int /*<<< orphan*/  memset (struct ta_xgmi_shared_memory*,int /*<<< orphan*/ ,int) ; 
 int psp_xgmi_invoke (struct psp_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_v11_0_xgmi_get_node_id(struct psp_context *psp, uint64_t *node_id)
{
	struct ta_xgmi_shared_memory *xgmi_cmd;
	int ret;

	xgmi_cmd = (struct ta_xgmi_shared_memory*)psp->xgmi_context.xgmi_shared_buf;
	memset(xgmi_cmd, 0, sizeof(struct ta_xgmi_shared_memory));

	xgmi_cmd->cmd_id = TA_COMMAND_XGMI__GET_NODE_ID;

	/* Invoke xgmi ta to get the node id */
	ret = psp_xgmi_invoke(psp, xgmi_cmd->cmd_id);
	if (ret)
		return ret;

	*node_id = xgmi_cmd->xgmi_out_message.get_node_id.node_id;

	return 0;
}