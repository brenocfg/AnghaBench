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
struct iwl_txq {TYPE_2__* entries; int /*<<< orphan*/  write_ptr; int /*<<< orphan*/  read_ptr; } ;
struct iwl_trans_pcie {size_t cmd_queue; int /*<<< orphan*/  wait_command_queue; struct iwl_txq** txq; } ;
struct iwl_trans {int /*<<< orphan*/  status; } ;
struct iwl_host_cmd {int flags; int /*<<< orphan*/ * resp_pkt; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ meta; } ;

/* Variables and functions */
 int CMD_SEND_IN_RFKILL ; 
 int CMD_WANT_SKB ; 
 int EIO ; 
 int ERFKILL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HOST_COMPLETE_TIMEOUT ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*,char const*) ; 
 int /*<<< orphan*/  IWL_DEBUG_RF_KILL (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,char const*,...) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  STATUS_FW_ERROR ; 
 int /*<<< orphan*/  STATUS_RFKILL_OPMODE ; 
 int /*<<< orphan*/  STATUS_SYNC_HCMD_ACTIVE ; 
 scalar_t__ WARN (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 char* iwl_get_cmd_string (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_pcie_gen2_enqueue_hcmd (struct iwl_trans*,struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_sync_nmi (struct iwl_trans*) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_pcie_gen2_send_hcmd_sync(struct iwl_trans *trans,
					struct iwl_host_cmd *cmd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	const char *cmd_str = iwl_get_cmd_string(trans, cmd->id);
	struct iwl_txq *txq = trans_pcie->txq[trans_pcie->cmd_queue];
	int cmd_idx;
	int ret;

	IWL_DEBUG_INFO(trans, "Attempting to send sync command %s\n", cmd_str);

	if (WARN(test_and_set_bit(STATUS_SYNC_HCMD_ACTIVE,
				  &trans->status),
		 "Command %s: a command is already active!\n", cmd_str))
		return -EIO;

	IWL_DEBUG_INFO(trans, "Setting HCMD_ACTIVE for command %s\n", cmd_str);

	cmd_idx = iwl_pcie_gen2_enqueue_hcmd(trans, cmd);
	if (cmd_idx < 0) {
		ret = cmd_idx;
		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		IWL_ERR(trans, "Error sending %s: enqueue_hcmd failed: %d\n",
			cmd_str, ret);
		return ret;
	}

	ret = wait_event_timeout(trans_pcie->wait_command_queue,
				 !test_bit(STATUS_SYNC_HCMD_ACTIVE,
					   &trans->status),
				 HOST_COMPLETE_TIMEOUT);
	if (!ret) {
		IWL_ERR(trans, "Error sending %s: time out after %dms.\n",
			cmd_str, jiffies_to_msecs(HOST_COMPLETE_TIMEOUT));

		IWL_ERR(trans, "Current CMD queue read_ptr %d write_ptr %d\n",
			txq->read_ptr, txq->write_ptr);

		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		IWL_DEBUG_INFO(trans, "Clearing HCMD_ACTIVE for command %s\n",
			       cmd_str);
		ret = -ETIMEDOUT;

		iwl_trans_pcie_sync_nmi(trans);
		goto cancel;
	}

	if (test_bit(STATUS_FW_ERROR, &trans->status)) {
		IWL_ERR(trans, "FW error in SYNC CMD %s\n", cmd_str);
		dump_stack();
		ret = -EIO;
		goto cancel;
	}

	if (!(cmd->flags & CMD_SEND_IN_RFKILL) &&
	    test_bit(STATUS_RFKILL_OPMODE, &trans->status)) {
		IWL_DEBUG_RF_KILL(trans, "RFKILL in SYNC CMD... no rsp\n");
		ret = -ERFKILL;
		goto cancel;
	}

	if ((cmd->flags & CMD_WANT_SKB) && !cmd->resp_pkt) {
		IWL_ERR(trans, "Error: Response NULL in '%s'\n", cmd_str);
		ret = -EIO;
		goto cancel;
	}

	return 0;

cancel:
	if (cmd->flags & CMD_WANT_SKB) {
		/*
		 * Cancel the CMD_WANT_SKB flag for the cmd in the
		 * TX cmd queue. Otherwise in case the cmd comes
		 * in later, it will possibly set an invalid
		 * address (cmd->meta.source).
		 */
		txq->entries[cmd_idx].meta.flags &= ~CMD_WANT_SKB;
	}

	if (cmd->resp_pkt) {
		iwl_free_resp(cmd);
		cmd->resp_pkt = NULL;
	}

	return ret;
}