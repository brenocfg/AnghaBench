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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_trans_txq_scd_cfg {int tid; int aggregate; int /*<<< orphan*/  fifo; int /*<<< orphan*/  frame_limit; int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm_tid_data {int txq_id; scalar_t__ seq_number; } ;
struct iwl_mvm_sta {size_t reserved_queue; int /*<<< orphan*/  sta_id; struct iwl_mvm_tid_data* tid_data; int /*<<< orphan*/  vif; } ;
struct iwl_mvm {TYPE_1__* queue_info; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 size_t IEEE80211_INVAL_HW_QUEUE ; 
 int /*<<< orphan*/  IEEE80211_SEQ_TO_SN (scalar_t__) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  IWL_FRAME_LIMIT ; 
 int IWL_MAX_TID_COUNT ; 
 int IWL_MVM_DQA_BSS_CLIENT_QUEUE ; 
 int IWL_MVM_DQA_MIN_DATA_QUEUE ; 
 int IWL_MVM_INVALID_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_QUEUE_READY ; 
 int /*<<< orphan*/  IWL_MVM_QUEUE_RESERVED ; 
 int /*<<< orphan*/  iwl_mvm_enable_txq (struct iwl_mvm*,struct ieee80211_sta*,int,int /*<<< orphan*/ ,struct iwl_trans_txq_scd_cfg*,unsigned int) ; 
 unsigned int iwl_mvm_get_wd_timeout (struct iwl_mvm*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ac_to_tx_fifo (struct iwl_mvm*,int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int iwl_mvm_tvqm_enable_txq (struct iwl_mvm*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int* tid_to_mac80211_ac ; 

__attribute__((used)) static void iwl_mvm_realloc_queues_after_restart(struct iwl_mvm *mvm,
						 struct ieee80211_sta *sta)
{
	struct iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	unsigned int wdg =
		iwl_mvm_get_wd_timeout(mvm, mvm_sta->vif, false, false);
	int i;
	struct iwl_trans_txq_scd_cfg cfg = {
		.sta_id = mvm_sta->sta_id,
		.frame_limit = IWL_FRAME_LIMIT,
	};

	/* Make sure reserved queue is still marked as such (if allocated) */
	if (mvm_sta->reserved_queue != IEEE80211_INVAL_HW_QUEUE)
		mvm->queue_info[mvm_sta->reserved_queue].status =
			IWL_MVM_QUEUE_RESERVED;

	for (i = 0; i <= IWL_MAX_TID_COUNT; i++) {
		struct iwl_mvm_tid_data *tid_data = &mvm_sta->tid_data[i];
		int txq_id = tid_data->txq_id;
		int ac;

		if (txq_id == IWL_MVM_INVALID_QUEUE)
			continue;

		ac = tid_to_mac80211_ac[i];

		if (iwl_mvm_has_new_tx_api(mvm)) {
			IWL_DEBUG_TX_QUEUES(mvm,
					    "Re-mapping sta %d tid %d\n",
					    mvm_sta->sta_id, i);
			txq_id = iwl_mvm_tvqm_enable_txq(mvm, mvm_sta->sta_id,
							 i, wdg);
			/*
			 * on failures, just set it to IWL_MVM_INVALID_QUEUE
			 * to try again later, we have no other good way of
			 * failing here
			 */
			if (txq_id < 0)
				txq_id = IWL_MVM_INVALID_QUEUE;
			tid_data->txq_id = txq_id;

			/*
			 * Since we don't set the seq number after reset, and HW
			 * sets it now, FW reset will cause the seq num to start
			 * at 0 again, so driver will need to update it
			 * internally as well, so it keeps in sync with real val
			 */
			tid_data->seq_number = 0;
		} else {
			u16 seq = IEEE80211_SEQ_TO_SN(tid_data->seq_number);

			cfg.tid = i;
			cfg.fifo = iwl_mvm_mac_ac_to_tx_fifo(mvm, ac);
			cfg.aggregate = (txq_id >= IWL_MVM_DQA_MIN_DATA_QUEUE ||
					 txq_id ==
					 IWL_MVM_DQA_BSS_CLIENT_QUEUE);

			IWL_DEBUG_TX_QUEUES(mvm,
					    "Re-mapping sta %d tid %d to queue %d\n",
					    mvm_sta->sta_id, i, txq_id);

			iwl_mvm_enable_txq(mvm, sta, txq_id, seq, &cfg, wdg);
			mvm->queue_info[txq_id].status = IWL_MVM_QUEUE_READY;
		}
	}
}