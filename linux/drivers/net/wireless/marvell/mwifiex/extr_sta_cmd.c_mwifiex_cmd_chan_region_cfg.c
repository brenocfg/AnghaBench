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
typedef  scalar_t__ u16 ;
struct mwifiex_private {int dummy; } ;
struct host_cmd_ds_chan_region_cfg {void* action; } ;
struct TYPE_2__ {struct host_cmd_ds_chan_region_cfg reg_cfg; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ HostCmd_ACT_GEN_GET ; 
 scalar_t__ HostCmd_CMD_CHAN_REGION_CFG ; 
 scalar_t__ S_DS_GEN ; 
 void* cpu_to_le16 (scalar_t__) ; 

__attribute__((used)) static int mwifiex_cmd_chan_region_cfg(struct mwifiex_private *priv,
				       struct host_cmd_ds_command *cmd,
				       u16 cmd_action)
{
	struct host_cmd_ds_chan_region_cfg *reg = &cmd->params.reg_cfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_CHAN_REGION_CFG);
	cmd->size = cpu_to_le16(sizeof(*reg) + S_DS_GEN);

	if (cmd_action == HostCmd_ACT_GEN_GET)
		reg->action = cpu_to_le16(cmd_action);

	return 0;
}