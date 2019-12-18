#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ta_xgmi_cmd_get_topology_info_input {int num_nodes; TYPE_3__* nodes; } ;
struct TYPE_6__ {struct ta_xgmi_cmd_get_topology_info_input get_topology_info; } ;
struct ta_xgmi_shared_memory {int /*<<< orphan*/  cmd_id; TYPE_2__ xgmi_in_message; } ;
struct psp_xgmi_topology_info {scalar_t__ num_nodes; TYPE_4__* nodes; } ;
struct TYPE_5__ {scalar_t__ xgmi_shared_buf; } ;
struct psp_context {TYPE_1__ xgmi_context; } ;
struct TYPE_8__ {int /*<<< orphan*/  sdma_engine; int /*<<< orphan*/  num_hops; int /*<<< orphan*/  node_id; } ;
struct TYPE_7__ {int is_sharing_enabled; int /*<<< orphan*/  sdma_engine; int /*<<< orphan*/  num_hops; int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TA_COMMAND_XGMI__SET_TOPOLOGY_INFO ; 
 scalar_t__ TA_XGMI__MAX_CONNECTED_NODES ; 
 int /*<<< orphan*/  memset (struct ta_xgmi_shared_memory*,int /*<<< orphan*/ ,int) ; 
 int psp_xgmi_invoke (struct psp_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_v11_0_xgmi_set_topology_info(struct psp_context *psp,
	int number_devices, struct psp_xgmi_topology_info *topology)
{
	struct ta_xgmi_shared_memory *xgmi_cmd;
	struct ta_xgmi_cmd_get_topology_info_input *topology_info_input;
	int i;

	if (!topology || topology->num_nodes > TA_XGMI__MAX_CONNECTED_NODES)
		return -EINVAL;

	xgmi_cmd = (struct ta_xgmi_shared_memory*)psp->xgmi_context.xgmi_shared_buf;
	memset(xgmi_cmd, 0, sizeof(struct ta_xgmi_shared_memory));

	topology_info_input = &xgmi_cmd->xgmi_in_message.get_topology_info;
	xgmi_cmd->cmd_id = TA_COMMAND_XGMI__SET_TOPOLOGY_INFO;
	topology_info_input->num_nodes = number_devices;

	for (i = 0; i < topology_info_input->num_nodes; i++) {
		topology_info_input->nodes[i].node_id = topology->nodes[i].node_id;
		topology_info_input->nodes[i].num_hops = topology->nodes[i].num_hops;
		topology_info_input->nodes[i].is_sharing_enabled = 1;
		topology_info_input->nodes[i].sdma_engine = topology->nodes[i].sdma_engine;
	}

	/* Invoke xgmi ta to set topology information */
	return psp_xgmi_invoke(psp, TA_COMMAND_XGMI__SET_TOPOLOGY_INFO);
}