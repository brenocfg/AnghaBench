#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u16 ;
struct iwl_mvm_tid_data {int /*<<< orphan*/  ssn; } ;
struct iwl_mvm_sta {struct iwl_mvm_tid_data* tid_data; } ;
struct iwl_mvm {int /*<<< orphan*/  fwrt; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct iwl_fw_dbg_trigger_ba {int /*<<< orphan*/  rx_ba_stop; int /*<<< orphan*/  rx_ba_start; int /*<<< orphan*/  tx_ba_stop; int /*<<< orphan*/  tx_ba_start; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_BA_TRIGGER (struct iwl_mvm*,struct iwl_fw_dbg_trigger_tlv*,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ,size_t,...) ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_BA ; 
#define  IEEE80211_AMPDU_RX_START 131 
#define  IEEE80211_AMPDU_RX_STOP 130 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 129 
#define  IEEE80211_AMPDU_TX_STOP_CONT 128 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_trigger_on (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 

__attribute__((used)) static void
iwl_mvm_ampdu_check_trigger(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			    struct ieee80211_sta *sta, u16 tid, u16 rx_ba_ssn,
			    enum ieee80211_ampdu_mlme_action action)
{
	struct iwl_fw_dbg_trigger_tlv *trig;
	struct iwl_fw_dbg_trigger_ba *ba_trig;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vif_to_wdev(vif),
				     FW_DBG_TRIGGER_BA);
	if (!trig)
		return;

	ba_trig = (void *)trig->data;

	switch (action) {
	case IEEE80211_AMPDU_TX_OPERATIONAL: {
		struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
		struct iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];

		CHECK_BA_TRIGGER(mvm, trig, ba_trig->tx_ba_start, tid,
				 "TX AGG START: MAC %pM tid %d ssn %d\n",
				 sta->addr, tid, tid_data->ssn);
		break;
		}
	case IEEE80211_AMPDU_TX_STOP_CONT:
		CHECK_BA_TRIGGER(mvm, trig, ba_trig->tx_ba_stop, tid,
				 "TX AGG STOP: MAC %pM tid %d\n",
				 sta->addr, tid);
		break;
	case IEEE80211_AMPDU_RX_START:
		CHECK_BA_TRIGGER(mvm, trig, ba_trig->rx_ba_start, tid,
				 "RX AGG START: MAC %pM tid %d ssn %d\n",
				 sta->addr, tid, rx_ba_ssn);
		break;
	case IEEE80211_AMPDU_RX_STOP:
		CHECK_BA_TRIGGER(mvm, trig, ba_trig->rx_ba_stop, tid,
				 "RX AGG STOP: MAC %pM tid %d\n",
				 sta->addr, tid);
		break;
	default:
		break;
	}
}