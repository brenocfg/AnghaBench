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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct iwl_tlc_update_notif {size_t sta_id; int /*<<< orphan*/  amsdu_size; int /*<<< orphan*/  amsdu_enabled; int /*<<< orphan*/  rate; int /*<<< orphan*/  flags; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_lq_sta_rs_fw {void* last_rate_n_flags; } ;
struct TYPE_2__ {struct iwl_lq_sta_rs_fw rs_fw; } ;
struct iwl_mvm_sta {int amsdu_enabled; scalar_t__ max_amsdu_len; int /*<<< orphan*/  orig_amsdu_len; TYPE_1__ lq_sta; } ;
struct iwl_mvm {int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct ieee80211_sta {scalar_t__ max_amsdu_len; int* max_tid_amsdu_len; scalar_t__ max_rc_amsdu_len; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*,void*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,size_t) ; 
 int IWL_MAX_TID_COUNT ; 
 int IWL_TLC_NOTIF_FLAG_AMSDU ; 
 int IWL_TLC_NOTIF_FLAG_RATE ; 
 scalar_t__ WARN_ON (int) ; 
 int iwl_mvm_max_amsdu_size (struct iwl_mvm*,struct ieee80211_sta*,int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

void iwl_mvm_tlc_update_notif(struct iwl_mvm *mvm,
			      struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_tlc_update_notif *notif;
	struct ieee80211_sta *sta;
	struct iwl_mvm_sta *mvmsta;
	struct iwl_lq_sta_rs_fw *lq_sta;
	u32 flags;

	rcu_read_lock();

	notif = (void *)pkt->data;
	sta = rcu_dereference(mvm->fw_id_to_mac_id[notif->sta_id]);
	if (IS_ERR_OR_NULL(sta)) {
		IWL_ERR(mvm, "Invalid sta id (%d) in FW TLC notification\n",
			notif->sta_id);
		goto out;
	}

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	if (!mvmsta) {
		IWL_ERR(mvm, "Invalid sta id (%d) in FW TLC notification\n",
			notif->sta_id);
		goto out;
	}

	flags = le32_to_cpu(notif->flags);

	lq_sta = &mvmsta->lq_sta.rs_fw;

	if (flags & IWL_TLC_NOTIF_FLAG_RATE) {
		lq_sta->last_rate_n_flags = le32_to_cpu(notif->rate);
		IWL_DEBUG_RATE(mvm, "new rate_n_flags: 0x%X\n",
			       lq_sta->last_rate_n_flags);
	}

	if (flags & IWL_TLC_NOTIF_FLAG_AMSDU && !mvmsta->orig_amsdu_len) {
		u16 size = le32_to_cpu(notif->amsdu_size);
		int i;

		if (WARN_ON(sta->max_amsdu_len < size))
			goto out;

		mvmsta->amsdu_enabled = le32_to_cpu(notif->amsdu_enabled);
		mvmsta->max_amsdu_len = size;
		sta->max_rc_amsdu_len = mvmsta->max_amsdu_len;

		for (i = 0; i < IWL_MAX_TID_COUNT; i++) {
			if (mvmsta->amsdu_enabled & BIT(i))
				sta->max_tid_amsdu_len[i] =
					iwl_mvm_max_amsdu_size(mvm, sta, i);
			else
				/*
				 * Not so elegant, but this will effectively
				 * prevent AMSDU on this TID
				 */
				sta->max_tid_amsdu_len[i] = 1;
		}

		IWL_DEBUG_RATE(mvm,
			       "AMSDU update. AMSDU size: %d, AMSDU selected size: %d, AMSDU TID bitmap 0x%X\n",
			       le32_to_cpu(notif->amsdu_size), size,
			       mvmsta->amsdu_enabled);
	}
out:
	rcu_read_unlock();
}