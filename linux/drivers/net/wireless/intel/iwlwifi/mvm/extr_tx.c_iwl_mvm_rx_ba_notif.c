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
typedef  void* u8 ;
typedef  scalar_t__ u16 ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_tid_data {scalar_t__ rate_n_flags; scalar_t__ tx_time; void* lq_color; } ;
struct iwl_mvm_sta {struct iwl_mvm_tid_data* tid_data; } ;
struct iwl_mvm_compressed_ba_tfd {int tid; int /*<<< orphan*/  tfd_index; int /*<<< orphan*/  q_num; } ;
struct iwl_mvm_compressed_ba_notif {int sta_id; int /*<<< orphan*/  done; int /*<<< orphan*/  txed; int /*<<< orphan*/  flags; int /*<<< orphan*/  wireless_time; int /*<<< orphan*/  tx_rate; struct iwl_mvm_compressed_ba_tfd* tfd; int /*<<< orphan*/  tfd_cnt; scalar_t__ reduced_txp; int /*<<< orphan*/  tlc_rate_info; } ;
struct iwl_mvm_ba_notif {int sta_id; int tid; scalar_t__ reduced_txp; void* txed_2_done; void* txed; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  seq_ctl; int /*<<< orphan*/  sta_addr; int /*<<< orphan*/  scd_ssn; int /*<<< orphan*/  scd_flow; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_2__ {void** status_driver_data; scalar_t__ tx_time; void* ampdu_len; void* ampdu_ack_len; } ;
struct ieee80211_tx_info {TYPE_1__ status; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_TX_STAT_AMPDU ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_REPLY (struct iwl_mvm*,char*,int,...) ; 
 int IWL_MAX_TID_COUNT ; 
 int IWL_MGMT_TID ; 
 void* TX_RES_RATE_TABLE_COL_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_staid_rcu (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  iwl_mvm_tx_airtime (struct iwl_mvm*,struct iwl_mvm_sta*,scalar_t__) ; 
 int /*<<< orphan*/  iwl_mvm_tx_reclaim (struct iwl_mvm*,int,int,int,int,struct ieee80211_tx_info*,scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_rx_ba_notif(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	int sta_id, tid, txq, index;
	struct ieee80211_tx_info ba_info = {};
	struct iwl_mvm_ba_notif *ba_notif;
	struct iwl_mvm_tid_data *tid_data;
	struct iwl_mvm_sta *mvmsta;

	ba_info.flags = IEEE80211_TX_STAT_AMPDU;

	if (iwl_mvm_has_new_tx_api(mvm)) {
		struct iwl_mvm_compressed_ba_notif *ba_res =
			(void *)pkt->data;
		u8 lq_color = TX_RES_RATE_TABLE_COL_GET(ba_res->tlc_rate_info);
		int i;

		sta_id = ba_res->sta_id;
		ba_info.status.ampdu_ack_len = (u8)le16_to_cpu(ba_res->done);
		ba_info.status.ampdu_len = (u8)le16_to_cpu(ba_res->txed);
		ba_info.status.tx_time =
			(u16)le32_to_cpu(ba_res->wireless_time);
		ba_info.status.status_driver_data[0] =
			(void *)(uintptr_t)ba_res->reduced_txp;

		if (!le16_to_cpu(ba_res->tfd_cnt))
			goto out;

		rcu_read_lock();

		mvmsta = iwl_mvm_sta_from_staid_rcu(mvm, sta_id);
		if (!mvmsta)
			goto out_unlock;

		/* Free per TID */
		for (i = 0; i < le16_to_cpu(ba_res->tfd_cnt); i++) {
			struct iwl_mvm_compressed_ba_tfd *ba_tfd =
				&ba_res->tfd[i];

			tid = ba_tfd->tid;
			if (tid == IWL_MGMT_TID)
				tid = IWL_MAX_TID_COUNT;

			mvmsta->tid_data[i].lq_color = lq_color;
			iwl_mvm_tx_reclaim(mvm, sta_id, tid,
					   (int)(le16_to_cpu(ba_tfd->q_num)),
					   le16_to_cpu(ba_tfd->tfd_index),
					   &ba_info,
					   le32_to_cpu(ba_res->tx_rate));
		}

		iwl_mvm_tx_airtime(mvm, mvmsta,
				   le32_to_cpu(ba_res->wireless_time));
out_unlock:
		rcu_read_unlock();
out:
		IWL_DEBUG_TX_REPLY(mvm,
				   "BA_NOTIFICATION Received from sta_id = %d, flags %x, sent:%d, acked:%d\n",
				   sta_id, le32_to_cpu(ba_res->flags),
				   le16_to_cpu(ba_res->txed),
				   le16_to_cpu(ba_res->done));
		return;
	}

	ba_notif = (void *)pkt->data;
	sta_id = ba_notif->sta_id;
	tid = ba_notif->tid;
	/* "flow" corresponds to Tx queue */
	txq = le16_to_cpu(ba_notif->scd_flow);
	/* "ssn" is start of block-ack Tx window, corresponds to index
	 * (in Tx queue's circular buffer) of first TFD/frame in window */
	index = le16_to_cpu(ba_notif->scd_ssn);

	rcu_read_lock();
	mvmsta = iwl_mvm_sta_from_staid_rcu(mvm, sta_id);
	if (WARN_ON_ONCE(!mvmsta)) {
		rcu_read_unlock();
		return;
	}

	tid_data = &mvmsta->tid_data[tid];

	ba_info.status.ampdu_ack_len = ba_notif->txed_2_done;
	ba_info.status.ampdu_len = ba_notif->txed;
	ba_info.status.tx_time = tid_data->tx_time;
	ba_info.status.status_driver_data[0] =
		(void *)(uintptr_t)ba_notif->reduced_txp;

	rcu_read_unlock();

	iwl_mvm_tx_reclaim(mvm, sta_id, tid, txq, index, &ba_info,
			   tid_data->rate_n_flags);

	IWL_DEBUG_TX_REPLY(mvm,
			   "BA_NOTIFICATION Received from %pM, sta_id = %d\n",
			   ba_notif->sta_addr, ba_notif->sta_id);

	IWL_DEBUG_TX_REPLY(mvm,
			   "TID = %d, SeqCtl = %d, bitmap = 0x%llx, scd_flow = %d, scd_ssn = %d sent:%d, acked:%d\n",
			   ba_notif->tid, le16_to_cpu(ba_notif->seq_ctl),
			   le64_to_cpu(ba_notif->bitmap), txq, index,
			   ba_notif->txed, ba_notif->txed_2_done);

	IWL_DEBUG_TX_REPLY(mvm, "reduced txp from ba notif %d\n",
			   ba_notif->reduced_txp);
}