#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct iwl_mvm_vif {size_t id; int /*<<< orphan*/  uapsd_nonagg_detected_wk; int /*<<< orphan*/  ap_sta_id; } ;
struct iwl_mvm_tcm_mac {int opened_rx_ba_sessions; } ;
struct TYPE_5__ {struct iwl_mvm_tcm_mac* data; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; TYPE_2__ tcm; TYPE_1__* nvm_data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_ampdu_params {int action; size_t tid; size_t ssn; size_t buf_size; int amsdu; size_t timeout; struct ieee80211_sta* sta; } ;
typedef  enum ieee80211_ampdu_mlme_action { ____Placeholder_ieee80211_ampdu_mlme_action } ieee80211_ampdu_mlme_action ;
struct TYPE_6__ {int /*<<< orphan*/  sta_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  sku_cap_11n_enable; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
#define  IEEE80211_AMPDU_RX_START 134 
#define  IEEE80211_AMPDU_RX_STOP 133 
#define  IEEE80211_AMPDU_TX_OPERATIONAL 132 
#define  IEEE80211_AMPDU_TX_START 131 
#define  IEEE80211_AMPDU_TX_STOP_CONT 130 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH 129 
#define  IEEE80211_AMPDU_TX_STOP_FLUSH_CONT 128 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_mvm*,char*,int /*<<< orphan*/ ,size_t,int) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_enable_rx_ampdu () ; 
 int /*<<< orphan*/  iwl_enable_tx_ampdu () ; 
 int /*<<< orphan*/  iwl_mvm_ampdu_check_trigger (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,size_t,size_t,int) ; 
 TYPE_3__* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int iwl_mvm_sta_rx_agg (struct iwl_mvm*,struct ieee80211_sta*,size_t,size_t,int,size_t,size_t) ; 
 int iwl_mvm_sta_tx_agg_flush (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,size_t) ; 
 int iwl_mvm_sta_tx_agg_oper (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,size_t,size_t,int) ; 
 int iwl_mvm_sta_tx_agg_start (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,size_t,size_t*) ; 
 int iwl_mvm_sta_tx_agg_stop (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,size_t) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_mac_ampdu_action(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    struct ieee80211_ampdu_params *params)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	int ret;
	struct ieee80211_sta *sta = params->sta;
	enum ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;
	u16 buf_size = params->buf_size;
	bool amsdu = params->amsdu;
	u16 timeout = params->timeout;

	IWL_DEBUG_HT(mvm, "A-MPDU action on addr %pM tid %d: action %d\n",
		     sta->addr, tid, action);

	if (!(mvm->nvm_data->sku_cap_11n_enable))
		return -EACCES;

	mutex_lock(&mvm->mutex);

	switch (action) {
	case IEEE80211_AMPDU_RX_START:
		if (iwl_mvm_vif_from_mac80211(vif)->ap_sta_id ==
				iwl_mvm_sta_from_mac80211(sta)->sta_id) {
			struct iwl_mvm_vif *mvmvif;
			u16 macid = iwl_mvm_vif_from_mac80211(vif)->id;
			struct iwl_mvm_tcm_mac *mdata = &mvm->tcm.data[macid];

			mdata->opened_rx_ba_sessions = true;
			mvmvif = iwl_mvm_vif_from_mac80211(vif);
			cancel_delayed_work(&mvmvif->uapsd_nonagg_detected_wk);
		}
		if (!iwl_enable_rx_ampdu()) {
			ret = -EINVAL;
			break;
		}
		ret = iwl_mvm_sta_rx_agg(mvm, sta, tid, *ssn, true, buf_size,
					 timeout);
		break;
	case IEEE80211_AMPDU_RX_STOP:
		ret = iwl_mvm_sta_rx_agg(mvm, sta, tid, 0, false, buf_size,
					 timeout);
		break;
	case IEEE80211_AMPDU_TX_START:
		if (!iwl_enable_tx_ampdu()) {
			ret = -EINVAL;
			break;
		}
		ret = iwl_mvm_sta_tx_agg_start(mvm, vif, sta, tid, ssn);
		break;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		ret = iwl_mvm_sta_tx_agg_stop(mvm, vif, sta, tid);
		break;
	case IEEE80211_AMPDU_TX_STOP_FLUSH:
	case IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ret = iwl_mvm_sta_tx_agg_flush(mvm, vif, sta, tid);
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		ret = iwl_mvm_sta_tx_agg_oper(mvm, vif, sta, tid,
					      buf_size, amsdu);
		break;
	default:
		WARN_ON_ONCE(1);
		ret = -EINVAL;
		break;
	}

	if (!ret) {
		u16 rx_ba_ssn = 0;

		if (action == IEEE80211_AMPDU_RX_START)
			rx_ba_ssn = *ssn;

		iwl_mvm_ampdu_check_trigger(mvm, vif, sta, tid,
					    rx_ba_ssn, action);
	}
	mutex_unlock(&mvm->mutex);

	return ret;
}