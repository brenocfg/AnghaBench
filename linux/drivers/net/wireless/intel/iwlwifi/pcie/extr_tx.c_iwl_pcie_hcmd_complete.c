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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct page {int dummy; } ;
struct iwl_txq {int /*<<< orphan*/  lock; TYPE_2__* entries; int /*<<< orphan*/  write_ptr; int /*<<< orphan*/  read_ptr; } ;
struct iwl_trans_pcie {size_t cmd_queue; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  rx_page_order; struct iwl_txq** txq; } ;
struct iwl_trans {int /*<<< orphan*/  status; int /*<<< orphan*/  op_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  sequence; } ;
struct iwl_rx_packet {TYPE_1__ hdr; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  group_id; } ;
struct iwl_device_cmd {TYPE_3__ hdr; } ;
struct iwl_cmd_meta {int flags; TYPE_4__* source; } ;
struct TYPE_8__ {unsigned long _rx_page_addr; int /*<<< orphan*/  _rx_page_order; struct iwl_rx_packet* resp_pkt; } ;
struct TYPE_6__ {struct iwl_cmd_meta meta; struct iwl_device_cmd* cmd; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_WANT_ASYNC_CALLBACK ; 
 int CMD_WANT_SKB ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 int SEQ_TO_INDEX (int /*<<< orphan*/ ) ; 
 int SEQ_TO_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SYNC_HCMD_ACTIVE ; 
 scalar_t__ WARN (int,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_get_cmd_string (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_op_mode_async_cb (int /*<<< orphan*/ ,struct iwl_device_cmd*) ; 
 int /*<<< orphan*/  iwl_pcie_cmdq_reclaim (struct iwl_trans*,int,int) ; 
 int iwl_pcie_get_cmd_index (struct iwl_txq*,int) ; 
 int /*<<< orphan*/  iwl_pcie_tfd_unmap (struct iwl_trans*,struct iwl_cmd_meta*,struct iwl_txq*,int) ; 
 int /*<<< orphan*/  iwl_print_hex_error (struct iwl_trans*,struct iwl_rx_packet*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 struct page* rxb_steal_page (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iwl_pcie_hcmd_complete(struct iwl_trans *trans,
			    struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	u8 group_id;
	u32 cmd_id;
	int txq_id = SEQ_TO_QUEUE(sequence);
	int index = SEQ_TO_INDEX(sequence);
	int cmd_index;
	struct iwl_device_cmd *cmd;
	struct iwl_cmd_meta *meta;
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_txq *txq = trans_pcie->txq[trans_pcie->cmd_queue];

	/* If a Tx command is being handled and it isn't in the actual
	 * command queue then there a command routing bug has been introduced
	 * in the queue management code. */
	if (WARN(txq_id != trans_pcie->cmd_queue,
		 "wrong command queue %d (should be %d), sequence 0x%X readp=%d writep=%d\n",
		 txq_id, trans_pcie->cmd_queue, sequence, txq->read_ptr,
		 txq->write_ptr)) {
		iwl_print_hex_error(trans, pkt, 32);
		return;
	}

	spin_lock_bh(&txq->lock);

	cmd_index = iwl_pcie_get_cmd_index(txq, index);
	cmd = txq->entries[cmd_index].cmd;
	meta = &txq->entries[cmd_index].meta;
	group_id = cmd->hdr.group_id;
	cmd_id = iwl_cmd_id(cmd->hdr.cmd, group_id, 0);

	iwl_pcie_tfd_unmap(trans, meta, txq, index);

	/* Input error checking is done when commands are added to queue. */
	if (meta->flags & CMD_WANT_SKB) {
		struct page *p = rxb_steal_page(rxb);

		meta->source->resp_pkt = pkt;
		meta->source->_rx_page_addr = (unsigned long)page_address(p);
		meta->source->_rx_page_order = trans_pcie->rx_page_order;
	}

	if (meta->flags & CMD_WANT_ASYNC_CALLBACK)
		iwl_op_mode_async_cb(trans->op_mode, cmd);

	iwl_pcie_cmdq_reclaim(trans, txq_id, index);

	if (!(meta->flags & CMD_ASYNC)) {
		if (!test_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status)) {
			IWL_WARN(trans,
				 "HCMD_ACTIVE already clear for command %s\n",
				 iwl_get_cmd_string(trans, cmd_id));
		}
		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		IWL_DEBUG_INFO(trans, "Clearing HCMD_ACTIVE for command %s\n",
			       iwl_get_cmd_string(trans, cmd_id));
		wake_up(&trans_pcie->wait_command_queue);
	}

	meta->flags = 0;

	spin_unlock_bh(&txq->lock);
}