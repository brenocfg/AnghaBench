#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_private {struct mwifiex_adapter* adapter; } ;
struct TYPE_14__ {int last_cmd_index; int /*<<< orphan*/ * last_cmd_act; scalar_t__* last_cmd_id; int /*<<< orphan*/  num_cmd_host_to_card_failure; } ;
struct TYPE_13__ {int status; } ;
struct TYPE_12__ {int (* host_to_card ) (struct mwifiex_adapter*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ;} ;
struct mwifiex_adapter {scalar_t__ hw_status; scalar_t__ iface_type; int cmd_sent; int /*<<< orphan*/  cmd_timer; TYPE_4__ dbg; int /*<<< orphan*/  mwifiex_cmd_lock; struct cmd_ctrl_node* curr_cmd; TYPE_3__ cmd_wait_q; int /*<<< orphan*/  intf_hdr_len; TYPE_2__ if_ops; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  main_work; int /*<<< orphan*/  workqueue; } ;
struct host_cmd_ds_command {scalar_t__ size; scalar_t__ command; scalar_t__ seq_num; } ;
struct cmd_ctrl_node {scalar_t__ wait_q_enabled; TYPE_5__* cmd_skb; TYPE_1__* priv; scalar_t__ cmd_no; } ;
struct TYPE_15__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_11__ {int /*<<< orphan*/  bss_type; int /*<<< orphan*/  bss_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  CMD_D ; 
 int DBG_CMD_NUM ; 
 int EBUSY ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HostCmd_CMD_FUNC_INIT ; 
 scalar_t__ HostCmd_CMD_FUNC_SHUTDOWN ; 
 scalar_t__ HostCmd_CMD_FW_DUMP_EVENT ; 
 scalar_t__ HostCmd_CMD_ID_MASK ; 
 int /*<<< orphan*/  HostCmd_SET_SEQ_NO_BSS_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MWIFIEX_HW_STATUS_RESET ; 
 int /*<<< orphan*/  MWIFIEX_TIMER_10S ; 
 int /*<<< orphan*/  MWIFIEX_TYPE_CMD ; 
 int /*<<< orphan*/  MWIFIEX_TYPE_LEN ; 
 scalar_t__ MWIFIEX_USB ; 
 int /*<<< orphan*/  MWIFIEX_USB_EP_CMD_EVENT ; 
 int /*<<< orphan*/  MWIFIEX_USB_TYPE_CMD ; 
 int S_DS_GEN ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_dbg_dump (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,struct host_cmd_ds_command*,scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_recycle_cmd_node (struct mwifiex_adapter*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  skb_trim (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct mwifiex_adapter*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int stub2 (struct mwifiex_adapter*,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mwifiex_dnld_cmd_to_fw(struct mwifiex_private *priv,
				  struct cmd_ctrl_node *cmd_node)
{

	struct mwifiex_adapter *adapter = priv->adapter;
	int ret;
	struct host_cmd_ds_command *host_cmd;
	uint16_t cmd_code;
	uint16_t cmd_size;

	if (!adapter || !cmd_node)
		return -1;

	host_cmd = (struct host_cmd_ds_command *) (cmd_node->cmd_skb->data);

	/* Sanity test */
	if (host_cmd == NULL || host_cmd->size == 0) {
		mwifiex_dbg(adapter, ERROR,
			    "DNLD_CMD: host_cmd is null\t"
			    "or cmd size is 0, not sending\n");
		if (cmd_node->wait_q_enabled)
			adapter->cmd_wait_q.status = -1;
		mwifiex_recycle_cmd_node(adapter, cmd_node);
		return -1;
	}

	cmd_code = le16_to_cpu(host_cmd->command);
	cmd_node->cmd_no = cmd_code;
	cmd_size = le16_to_cpu(host_cmd->size);

	if (adapter->hw_status == MWIFIEX_HW_STATUS_RESET &&
	    cmd_code != HostCmd_CMD_FUNC_SHUTDOWN &&
	    cmd_code != HostCmd_CMD_FUNC_INIT) {
		mwifiex_dbg(adapter, ERROR,
			    "DNLD_CMD: FW in reset state, ignore cmd %#x\n",
			cmd_code);
		mwifiex_recycle_cmd_node(adapter, cmd_node);
		queue_work(adapter->workqueue, &adapter->main_work);
		return -1;
	}

	/* Set command sequence number */
	adapter->seq_num++;
	host_cmd->seq_num = cpu_to_le16(HostCmd_SET_SEQ_NO_BSS_INFO
					(adapter->seq_num,
					 cmd_node->priv->bss_num,
					 cmd_node->priv->bss_type));

	spin_lock_bh(&adapter->mwifiex_cmd_lock);
	adapter->curr_cmd = cmd_node;
	spin_unlock_bh(&adapter->mwifiex_cmd_lock);

	/* Adjust skb length */
	if (cmd_node->cmd_skb->len > cmd_size)
		/*
		 * cmd_size is less than sizeof(struct host_cmd_ds_command).
		 * Trim off the unused portion.
		 */
		skb_trim(cmd_node->cmd_skb, cmd_size);
	else if (cmd_node->cmd_skb->len < cmd_size)
		/*
		 * cmd_size is larger than sizeof(struct host_cmd_ds_command)
		 * because we have appended custom IE TLV. Increase skb length
		 * accordingly.
		 */
		skb_put(cmd_node->cmd_skb, cmd_size - cmd_node->cmd_skb->len);

	mwifiex_dbg(adapter, CMD,
		    "cmd: DNLD_CMD: %#x, act %#x, len %d, seqno %#x\n",
		    cmd_code,
		    get_unaligned_le16((u8 *)host_cmd + S_DS_GEN),
		    cmd_size, le16_to_cpu(host_cmd->seq_num));
	mwifiex_dbg_dump(adapter, CMD_D, "cmd buffer:", host_cmd, cmd_size);

	if (adapter->iface_type == MWIFIEX_USB) {
		skb_push(cmd_node->cmd_skb, MWIFIEX_TYPE_LEN);
		put_unaligned_le32(MWIFIEX_USB_TYPE_CMD,
				   cmd_node->cmd_skb->data);
		adapter->cmd_sent = true;
		ret = adapter->if_ops.host_to_card(adapter,
						   MWIFIEX_USB_EP_CMD_EVENT,
						   cmd_node->cmd_skb, NULL);
		skb_pull(cmd_node->cmd_skb, MWIFIEX_TYPE_LEN);
		if (ret == -EBUSY)
			cmd_node->cmd_skb = NULL;
	} else {
		skb_push(cmd_node->cmd_skb, adapter->intf_hdr_len);
		ret = adapter->if_ops.host_to_card(adapter, MWIFIEX_TYPE_CMD,
						   cmd_node->cmd_skb, NULL);
		skb_pull(cmd_node->cmd_skb, adapter->intf_hdr_len);
	}

	if (ret == -1) {
		mwifiex_dbg(adapter, ERROR,
			    "DNLD_CMD: host to card failed\n");
		if (adapter->iface_type == MWIFIEX_USB)
			adapter->cmd_sent = false;
		if (cmd_node->wait_q_enabled)
			adapter->cmd_wait_q.status = -1;
		mwifiex_recycle_cmd_node(adapter, adapter->curr_cmd);

		spin_lock_bh(&adapter->mwifiex_cmd_lock);
		adapter->curr_cmd = NULL;
		spin_unlock_bh(&adapter->mwifiex_cmd_lock);

		adapter->dbg.num_cmd_host_to_card_failure++;
		return -1;
	}

	/* Save the last command id and action to debug log */
	adapter->dbg.last_cmd_index =
			(adapter->dbg.last_cmd_index + 1) % DBG_CMD_NUM;
	adapter->dbg.last_cmd_id[adapter->dbg.last_cmd_index] = cmd_code;
	adapter->dbg.last_cmd_act[adapter->dbg.last_cmd_index] =
			get_unaligned_le16((u8 *)host_cmd + S_DS_GEN);

	/* Setup the timer after transmit command, except that specific
	 * command might not have command response.
	 */
	if (cmd_code != HostCmd_CMD_FW_DUMP_EVENT)
		mod_timer(&adapter->cmd_timer,
			  jiffies + msecs_to_jiffies(MWIFIEX_TIMER_10S));

	/* Clear BSS_NO_BITS from HostCmd */
	cmd_code &= HostCmd_CMD_ID_MASK;

	return 0;
}