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
typedef  scalar_t__ u16 ;
struct mwifiex_adapter {scalar_t__ ps_state; int /*<<< orphan*/  cmd_pending; int /*<<< orphan*/  cmd_pending_q_lock; int /*<<< orphan*/  cmd_pending_q; } ;
struct host_cmd_ds_802_11_ps_mode_enh {int /*<<< orphan*/  action; } ;
struct TYPE_4__ {struct host_cmd_ds_802_11_ps_mode_enh psmode_enh; } ;
struct host_cmd_ds_command {TYPE_2__ params; int /*<<< orphan*/  command; } ;
struct cmd_ctrl_node {int /*<<< orphan*/  list; TYPE_1__* cmd_skb; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 scalar_t__ DIS_AUTO_PS ; 
 scalar_t__ DIS_PS ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HostCmd_CMD_802_11_PS_MODE_ENH ; 
 scalar_t__ PS_STATE_AWAKE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void
mwifiex_insert_cmd_to_pending_q(struct mwifiex_adapter *adapter,
				struct cmd_ctrl_node *cmd_node)
{
	struct host_cmd_ds_command *host_cmd = NULL;
	u16 command;
	bool add_tail = true;

	host_cmd = (struct host_cmd_ds_command *) (cmd_node->cmd_skb->data);
	if (!host_cmd) {
		mwifiex_dbg(adapter, ERROR, "QUEUE_CMD: host_cmd is NULL\n");
		return;
	}

	command = le16_to_cpu(host_cmd->command);

	/* Exit_PS command needs to be queued in the header always. */
	if (command == HostCmd_CMD_802_11_PS_MODE_ENH) {
		struct host_cmd_ds_802_11_ps_mode_enh *pm =
						&host_cmd->params.psmode_enh;
		if ((le16_to_cpu(pm->action) == DIS_PS) ||
		    (le16_to_cpu(pm->action) == DIS_AUTO_PS)) {
			if (adapter->ps_state != PS_STATE_AWAKE)
				add_tail = false;
		}
	}

	spin_lock_bh(&adapter->cmd_pending_q_lock);
	if (add_tail)
		list_add_tail(&cmd_node->list, &adapter->cmd_pending_q);
	else
		list_add(&cmd_node->list, &adapter->cmd_pending_q);
	spin_unlock_bh(&adapter->cmd_pending_q_lock);

	atomic_inc(&adapter->cmd_pending);
	mwifiex_dbg(adapter, CMD,
		    "cmd: QUEUE_CMD: cmd=%#x, cmd_pending=%d\n",
		command, atomic_read(&adapter->cmd_pending));
}