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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct iwl_txq {int ampdu; int read_ptr; int write_ptr; int /*<<< orphan*/  wd_timeout; } ;
struct iwl_trans_txq_scd_cfg {int fifo; int /*<<< orphan*/  frame_limit; int /*<<< orphan*/  tid; int /*<<< orphan*/  sta_id; scalar_t__ aggregate; } ;
struct iwl_trans_pcie {int cmd_queue; scalar_t__ scd_set_active; scalar_t__ scd_base_addr; int /*<<< orphan*/  queue_used; struct iwl_txq** txq; } ;
struct iwl_trans {TYPE_1__* trans_cfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  mq_rx_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int BUILD_RAxTID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRAME_LIMIT ; 
 int /*<<< orphan*/  HBUS_TARG_WRPTR ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_trans*,char*,int,int,...) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ SCD_CONTEXT_QUEUE_OFFSET (int) ; 
 int SCD_QUEUE_CTX_REG2_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCD_QUEUE_RDPTR (int) ; 
 int /*<<< orphan*/  SCD_QUEUE_STATUS_BITS (int) ; 
 int SCD_QUEUE_STTS_REG_MSK ; 
 int SCD_QUEUE_STTS_REG_POS_ACTIVE ; 
 int SCD_QUEUE_STTS_REG_POS_TXF ; 
 int SCD_QUEUE_STTS_REG_POS_WSL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  WIN_SIZE ; 
 int /*<<< orphan*/  iwl_pcie_txq_set_ratid_map (struct iwl_trans*,int,int) ; 
 int /*<<< orphan*/  iwl_scd_enable_set_active (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_scd_txq_disable_agg (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_scd_txq_enable_agg (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_scd_txq_set_chain (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_scd_txq_set_inactive (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_trans_write_mem32 (struct iwl_trans*,scalar_t__,int) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

bool iwl_trans_pcie_txq_enable(struct iwl_trans *trans, int txq_id, u16 ssn,
			       const struct iwl_trans_txq_scd_cfg *cfg,
			       unsigned int wdg_timeout)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_txq *txq = trans_pcie->txq[txq_id];
	int fifo = -1;
	bool scd_bug = false;

	if (test_and_set_bit(txq_id, trans_pcie->queue_used))
		WARN_ONCE(1, "queue %d already used - expect issues", txq_id);

	txq->wd_timeout = msecs_to_jiffies(wdg_timeout);

	if (cfg) {
		fifo = cfg->fifo;

		/* Disable the scheduler prior configuring the cmd queue */
		if (txq_id == trans_pcie->cmd_queue &&
		    trans_pcie->scd_set_active)
			iwl_scd_enable_set_active(trans, 0);

		/* Stop this Tx queue before configuring it */
		iwl_scd_txq_set_inactive(trans, txq_id);

		/* Set this queue as a chain-building queue unless it is CMD */
		if (txq_id != trans_pcie->cmd_queue)
			iwl_scd_txq_set_chain(trans, txq_id);

		if (cfg->aggregate) {
			u16 ra_tid = BUILD_RAxTID(cfg->sta_id, cfg->tid);

			/* Map receiver-address / traffic-ID to this queue */
			iwl_pcie_txq_set_ratid_map(trans, ra_tid, txq_id);

			/* enable aggregations for the queue */
			iwl_scd_txq_enable_agg(trans, txq_id);
			txq->ampdu = true;
		} else {
			/*
			 * disable aggregations for the queue, this will also
			 * make the ra_tid mapping configuration irrelevant
			 * since it is now a non-AGG queue.
			 */
			iwl_scd_txq_disable_agg(trans, txq_id);

			ssn = txq->read_ptr;
		}
	} else {
		/*
		 * If we need to move the SCD write pointer by steps of
		 * 0x40, 0x80 or 0xc0, it gets stuck. Avoids this and let
		 * the op_mode know by returning true later.
		 * Do this only in case cfg is NULL since this trick can
		 * be done only if we have DQA enabled which is true for mvm
		 * only. And mvm never sets a cfg pointer.
		 * This is really ugly, but this is the easiest way out for
		 * this sad hardware issue.
		 * This bug has been fixed on devices 9000 and up.
		 */
		scd_bug = !trans->trans_cfg->mq_rx_supported &&
			!((ssn - txq->write_ptr) & 0x3f) &&
			(ssn != txq->write_ptr);
		if (scd_bug)
			ssn++;
	}

	/* Place first TFD at index corresponding to start sequence number.
	 * Assumes that ssn_idx is valid (!= 0xFFF) */
	txq->read_ptr = (ssn & 0xff);
	txq->write_ptr = (ssn & 0xff);
	iwl_write_direct32(trans, HBUS_TARG_WRPTR,
			   (ssn & 0xff) | (txq_id << 8));

	if (cfg) {
		u8 frame_limit = cfg->frame_limit;

		iwl_write_prph(trans, SCD_QUEUE_RDPTR(txq_id), ssn);

		/* Set up Tx window size and frame limit for this queue */
		iwl_trans_write_mem32(trans, trans_pcie->scd_base_addr +
				SCD_CONTEXT_QUEUE_OFFSET(txq_id), 0);
		iwl_trans_write_mem32(trans,
			trans_pcie->scd_base_addr +
			SCD_CONTEXT_QUEUE_OFFSET(txq_id) + sizeof(u32),
			SCD_QUEUE_CTX_REG2_VAL(WIN_SIZE, frame_limit) |
			SCD_QUEUE_CTX_REG2_VAL(FRAME_LIMIT, frame_limit));

		/* Set up status area in SRAM, map to Tx DMA/FIFO, activate */
		iwl_write_prph(trans, SCD_QUEUE_STATUS_BITS(txq_id),
			       (1 << SCD_QUEUE_STTS_REG_POS_ACTIVE) |
			       (cfg->fifo << SCD_QUEUE_STTS_REG_POS_TXF) |
			       (1 << SCD_QUEUE_STTS_REG_POS_WSL) |
			       SCD_QUEUE_STTS_REG_MSK);

		/* enable the scheduler for this queue (only) */
		if (txq_id == trans_pcie->cmd_queue &&
		    trans_pcie->scd_set_active)
			iwl_scd_enable_set_active(trans, BIT(txq_id));

		IWL_DEBUG_TX_QUEUES(trans,
				    "Activate queue %d on FIFO %d WrPtr: %d\n",
				    txq_id, fifo, ssn & 0xff);
	} else {
		IWL_DEBUG_TX_QUEUES(trans,
				    "Activate queue %d WrPtr: %d\n",
				    txq_id, ssn & 0xff);
	}

	return scd_bug;
}