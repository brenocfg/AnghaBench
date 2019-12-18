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
struct iwl_scd_txq_cfg_cmd {int scd_queue; int tid; int /*<<< orphan*/  sta_id; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  action; } ;
struct iwl_mvm_txq {int stopped; } ;
struct iwl_mvm {int /*<<< orphan*/  trans; TYPE_1__* queue_info; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int mac80211_ac; int txq_tid; int /*<<< orphan*/  tid_bitmap; int /*<<< orphan*/  ra_sta_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int,...) ; 
 int /*<<< orphan*/  IWL_FRAME_LIMIT ; 
 int /*<<< orphan*/  SCD_CFG_DISABLE_QUEUE ; 
 int /*<<< orphan*/  SCD_QUEUE_CFG ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int hweight16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iwl_mvm_ac_to_tx_fifo ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_reconfig_scd (struct iwl_mvm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_scd_txq_cfg_cmd*) ; 
 int /*<<< orphan*/  iwl_trans_txq_disable (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  iwl_trans_txq_enable_cfg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  iwl_trans_txq_set_shared_mode (int /*<<< orphan*/ ,int,int) ; 
 int iwl_trans_wait_tx_queues_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_redirect_queue(struct iwl_mvm *mvm, int queue, int tid,
				  int ac, int ssn, unsigned int wdg_timeout,
				  bool force, struct iwl_mvm_txq *txq)
{
	struct iwl_scd_txq_cfg_cmd cmd = {
		.scd_queue = queue,
		.action = SCD_CFG_DISABLE_QUEUE,
	};
	bool shared_queue;
	int ret;

	if (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		return -EINVAL;

	/*
	 * If the AC is lower than current one - FIFO needs to be redirected to
	 * the lowest one of the streams in the queue. Check if this is needed
	 * here.
	 * Notice that the enum ieee80211_ac_numbers is "flipped", so BK is with
	 * value 3 and VO with value 0, so to check if ac X is lower than ac Y
	 * we need to check if the numerical value of X is LARGER than of Y.
	 */
	if (ac <= mvm->queue_info[queue].mac80211_ac && !force) {
		IWL_DEBUG_TX_QUEUES(mvm,
				    "No redirection needed on TXQ #%d\n",
				    queue);
		return 0;
	}

	cmd.sta_id = mvm->queue_info[queue].ra_sta_id;
	cmd.tx_fifo = iwl_mvm_ac_to_tx_fifo[mvm->queue_info[queue].mac80211_ac];
	cmd.tid = mvm->queue_info[queue].txq_tid;
	shared_queue = hweight16(mvm->queue_info[queue].tid_bitmap) > 1;

	IWL_DEBUG_TX_QUEUES(mvm, "Redirecting TXQ #%d to FIFO #%d\n",
			    queue, iwl_mvm_ac_to_tx_fifo[ac]);

	/* Stop the queue and wait for it to empty */
	txq->stopped = true;

	ret = iwl_trans_wait_tx_queues_empty(mvm->trans, BIT(queue));
	if (ret) {
		IWL_ERR(mvm, "Error draining queue %d before reconfig\n",
			queue);
		ret = -EIO;
		goto out;
	}

	/* Before redirecting the queue we need to de-activate it */
	iwl_trans_txq_disable(mvm->trans, queue, false);
	ret = iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, 0, sizeof(cmd), &cmd);
	if (ret)
		IWL_ERR(mvm, "Failed SCD disable TXQ %d (ret=%d)\n", queue,
			ret);

	/* Make sure the SCD wrptr is correctly set before reconfiguring */
	iwl_trans_txq_enable_cfg(mvm->trans, queue, ssn, NULL, wdg_timeout);

	/* Update the TID "owner" of the queue */
	mvm->queue_info[queue].txq_tid = tid;

	/* TODO: Work-around SCD bug when moving back by multiples of 0x40 */

	/* Redirect to lower AC */
	iwl_mvm_reconfig_scd(mvm, queue, iwl_mvm_ac_to_tx_fifo[ac],
			     cmd.sta_id, tid, IWL_FRAME_LIMIT, ssn);

	/* Update AC marking of the queue */
	mvm->queue_info[queue].mac80211_ac = ac;

	/*
	 * Mark queue as shared in transport if shared
	 * Note this has to be done after queue enablement because enablement
	 * can also set this value, and there is no indication there to shared
	 * queues
	 */
	if (shared_queue)
		iwl_trans_txq_set_shared_mode(mvm->trans, queue, true);

out:
	/* Continue using the queue */
	txq->stopped = false;

	return ret;
}