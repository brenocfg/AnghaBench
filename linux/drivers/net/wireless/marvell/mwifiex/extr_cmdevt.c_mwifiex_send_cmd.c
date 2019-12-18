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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {scalar_t__ hw_status; int /*<<< orphan*/  main_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  dev; scalar_t__ mfg_mode; int /*<<< orphan*/  work_flags; } ;
struct host_cmd_ds_command {scalar_t__ result; int /*<<< orphan*/  command; } ;
struct cmd_ctrl_node {scalar_t__ wait_q_enabled; int /*<<< orphan*/  cmd_flag; TYPE_1__* cmd_skb; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_F_HOSTCMD ; 
 int /*<<< orphan*/  ERROR ; 
#define  HOST_CMD_APCMD_STA_LIST 133 
#define  HOST_CMD_APCMD_SYS_RESET 132 
 scalar_t__ HostCmd_CMD_802_11_HS_CFG_ENH ; 
 scalar_t__ HostCmd_CMD_802_11_SCAN ; 
 scalar_t__ HostCmd_CMD_802_11_SCAN_EXT ; 
 scalar_t__ HostCmd_CMD_FUNC_INIT ; 
#define  HostCmd_CMD_UAP_BSS_START 131 
#define  HostCmd_CMD_UAP_BSS_STOP 130 
#define  HostCmd_CMD_UAP_STA_DEAUTH 129 
#define  HostCmd_CMD_UAP_SYS_CONFIG 128 
 scalar_t__ MWIFIEX_HW_STATUS_RESET ; 
 int /*<<< orphan*/  MWIFIEX_IS_CMD_TIMEDOUT ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_ENABLING ; 
 int /*<<< orphan*/  MWIFIEX_IS_SUSPENDED ; 
 int /*<<< orphan*/  MWIFIEX_SURPRISE_REMOVED ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int mwifiex_cmd_host_cmd (struct mwifiex_private*,struct host_cmd_ds_command*,void*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 struct cmd_ctrl_node* mwifiex_get_cmd_node (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_init_cmd_node (struct mwifiex_private*,struct cmd_ctrl_node*,scalar_t__,void*,int) ; 
 int /*<<< orphan*/  mwifiex_insert_cmd_to_free_q (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  mwifiex_insert_cmd_to_pending_q (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  mwifiex_queue_scan_cmd (struct mwifiex_private*,struct cmd_ctrl_node*) ; 
 int mwifiex_sta_prepare_cmd (struct mwifiex_private*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,struct host_cmd_ds_command*) ; 
 int mwifiex_uap_prepare_cmd (struct mwifiex_private*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,struct host_cmd_ds_command*) ; 
 int mwifiex_wait_queue_complete (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put_zero (TYPE_1__*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mwifiex_send_cmd(struct mwifiex_private *priv, u16 cmd_no,
		     u16 cmd_action, u32 cmd_oid, void *data_buf, bool sync)
{
	int ret;
	struct mwifiex_adapter *adapter = priv->adapter;
	struct cmd_ctrl_node *cmd_node;
	struct host_cmd_ds_command *cmd_ptr;

	if (!adapter) {
		pr_err("PREP_CMD: adapter is NULL\n");
		return -1;
	}

	if (test_bit(MWIFIEX_IS_SUSPENDED, &adapter->work_flags)) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: device in suspended state\n");
		return -1;
	}

	if (test_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags) &&
	    cmd_no != HostCmd_CMD_802_11_HS_CFG_ENH) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: host entering sleep state\n");
		return -1;
	}

	if (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags)) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: card is removed\n");
		return -1;
	}

	if (test_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags)) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: FW is in bad state\n");
		return -1;
	}

	if (adapter->hw_status == MWIFIEX_HW_STATUS_RESET) {
		if (cmd_no != HostCmd_CMD_FUNC_INIT) {
			mwifiex_dbg(adapter, ERROR,
				    "PREP_CMD: FW in reset state\n");
			return -1;
		}
	}
	/* We don't expect commands in manufacturing mode. They are cooked
	 * in application and ready to download buffer is passed to the driver
	 */
	if (adapter->mfg_mode && cmd_no) {
		dev_dbg(adapter->dev, "Ignoring commands in manufacturing mode\n");
		return -1;
	}


	/* Get a new command node */
	cmd_node = mwifiex_get_cmd_node(adapter);

	if (!cmd_node) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: no free cmd node\n");
		return -1;
	}

	/* Initialize the command node */
	mwifiex_init_cmd_node(priv, cmd_node, cmd_no, data_buf, sync);

	if (!cmd_node->cmd_skb) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: no free cmd buf\n");
		return -1;
	}

	skb_put_zero(cmd_node->cmd_skb, sizeof(struct host_cmd_ds_command));

	cmd_ptr = (struct host_cmd_ds_command *) (cmd_node->cmd_skb->data);
	cmd_ptr->command = cpu_to_le16(cmd_no);
	cmd_ptr->result = 0;

	/* Prepare command */
	if (cmd_no) {
		switch (cmd_no) {
		case HostCmd_CMD_UAP_SYS_CONFIG:
		case HostCmd_CMD_UAP_BSS_START:
		case HostCmd_CMD_UAP_BSS_STOP:
		case HostCmd_CMD_UAP_STA_DEAUTH:
		case HOST_CMD_APCMD_SYS_RESET:
		case HOST_CMD_APCMD_STA_LIST:
			ret = mwifiex_uap_prepare_cmd(priv, cmd_no, cmd_action,
						      cmd_oid, data_buf,
						      cmd_ptr);
			break;
		default:
			ret = mwifiex_sta_prepare_cmd(priv, cmd_no, cmd_action,
						      cmd_oid, data_buf,
						      cmd_ptr);
			break;
		}
	} else {
		ret = mwifiex_cmd_host_cmd(priv, cmd_ptr, data_buf);
		cmd_node->cmd_flag |= CMD_F_HOSTCMD;
	}

	/* Return error, since the command preparation failed */
	if (ret) {
		mwifiex_dbg(adapter, ERROR,
			    "PREP_CMD: cmd %#x preparation failed\n",
			cmd_no);
		mwifiex_insert_cmd_to_free_q(adapter, cmd_node);
		return -1;
	}

	/* Send command */
	if (cmd_no == HostCmd_CMD_802_11_SCAN ||
	    cmd_no == HostCmd_CMD_802_11_SCAN_EXT) {
		mwifiex_queue_scan_cmd(priv, cmd_node);
	} else {
		mwifiex_insert_cmd_to_pending_q(adapter, cmd_node);
		queue_work(adapter->workqueue, &adapter->main_work);
		if (cmd_node->wait_q_enabled)
			ret = mwifiex_wait_queue_complete(adapter, cmd_node);
	}

	return ret;
}