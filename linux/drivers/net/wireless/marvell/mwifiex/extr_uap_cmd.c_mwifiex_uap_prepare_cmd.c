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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct host_cmd_ds_command {void* size; void* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  HOST_CMD_APCMD_STA_LIST 134 
#define  HOST_CMD_APCMD_SYS_RESET 133 
#define  HostCmd_CMD_CHAN_REPORT_REQUEST 132 
#define  HostCmd_CMD_UAP_BSS_START 131 
#define  HostCmd_CMD_UAP_BSS_STOP 130 
#define  HostCmd_CMD_UAP_STA_DEAUTH 129 
#define  HostCmd_CMD_UAP_SYS_CONFIG 128 
 int S_DS_GEN ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  mwifiex_cmd_issue_chan_report_request (struct mwifiex_private*,void*,void*) ; 
 int /*<<< orphan*/  mwifiex_cmd_uap_sta_deauth (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int /*<<< orphan*/  mwifiex_cmd_uap_sys_config (struct host_cmd_ds_command*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int mwifiex_uap_prepare_cmd(struct mwifiex_private *priv, u16 cmd_no,
			    u16 cmd_action, u32 type,
			    void *data_buf, void *cmd_buf)
{
	struct host_cmd_ds_command *cmd = cmd_buf;

	switch (cmd_no) {
	case HostCmd_CMD_UAP_SYS_CONFIG:
		if (mwifiex_cmd_uap_sys_config(cmd, cmd_action, type, data_buf))
			return -1;
		break;
	case HostCmd_CMD_UAP_BSS_START:
	case HostCmd_CMD_UAP_BSS_STOP:
	case HOST_CMD_APCMD_SYS_RESET:
	case HOST_CMD_APCMD_STA_LIST:
		cmd->command = cpu_to_le16(cmd_no);
		cmd->size = cpu_to_le16(S_DS_GEN);
		break;
	case HostCmd_CMD_UAP_STA_DEAUTH:
		if (mwifiex_cmd_uap_sta_deauth(priv, cmd, data_buf))
			return -1;
		break;
	case HostCmd_CMD_CHAN_REPORT_REQUEST:
		if (mwifiex_cmd_issue_chan_report_request(priv, cmd_buf,
							  data_buf))
			return -1;
		break;
	default:
		mwifiex_dbg(priv->adapter, ERROR,
			    "PREP_CMD: unknown cmd %#x\n", cmd_no);
		return -1;
	}

	return 0;
}