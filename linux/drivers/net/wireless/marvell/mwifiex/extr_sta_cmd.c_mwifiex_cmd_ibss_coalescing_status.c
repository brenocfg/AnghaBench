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
typedef  int u16 ;
struct host_cmd_ds_802_11_ibss_status {void* enable; void* action; } ;
struct TYPE_2__ {struct host_cmd_ds_802_11_ibss_status ibss_coalescing; } ;
struct host_cmd_ds_command {scalar_t__ result; void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
#define  HostCmd_ACT_GEN_GET 129 
#define  HostCmd_ACT_GEN_SET 128 
 int HostCmd_CMD_802_11_IBSS_COALESCING_STATUS ; 
 int S_DS_GEN ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static int mwifiex_cmd_ibss_coalescing_status(struct host_cmd_ds_command *cmd,
					      u16 cmd_action, u16 *enable)
{
	struct host_cmd_ds_802_11_ibss_status *ibss_coal =
		&(cmd->params.ibss_coalescing);

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_IBSS_COALESCING_STATUS);
	cmd->size = cpu_to_le16(sizeof(struct host_cmd_ds_802_11_ibss_status) +
				S_DS_GEN);
	cmd->result = 0;
	ibss_coal->action = cpu_to_le16(cmd_action);

	switch (cmd_action) {
	case HostCmd_ACT_GEN_SET:
		if (enable)
			ibss_coal->enable = cpu_to_le16(*enable);
		else
			ibss_coal->enable = 0;
		break;

		/* In other case.. Nothing to do */
	case HostCmd_ACT_GEN_GET:
	default:
		break;
	}

	return 0;
}