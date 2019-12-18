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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct mvm_statistics_general_v8 {int /*<<< orphan*/ * beacon_average_energy; int /*<<< orphan*/ * beacon_counter; } ;
struct mvm_statistics_general {int /*<<< orphan*/ * beacon_average_energy; int /*<<< orphan*/ * beacon_counter; } ;
struct TYPE_6__ {int ave_beacon_signal; int bt_coex_min_thold; int bt_coex_max_thold; int last_bt_coex_event; int last_cqm_event; } ;
struct TYPE_5__ {int /*<<< orphan*/  avg_signal; void* num_beacons; } ;
struct iwl_mvm_vif {size_t id; TYPE_3__ bf_data; TYPE_2__ beacon_stats; } ;
struct iwl_mvm_stat_data {int beacon_filter_average_energy; struct mvm_statistics_general_v8* general; int /*<<< orphan*/  mac_id; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int dummy; } ;
struct TYPE_4__ {int cqm_rssi_thold; int cqm_rssi_hyst; } ;
struct ieee80211_vif {scalar_t__ type; int driver_flags; TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH ; 
 int /*<<< orphan*/  NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RSSI_EVENT_HIGH ; 
 int /*<<< orphan*/  RSSI_EVENT_LOW ; 
 int /*<<< orphan*/  ieee80211_cqm_rssi_notify (struct ieee80211_vif*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_bt_rssi_event (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_has_new_rx_stats_api (struct iwl_mvm*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_stat_iterator(void *_data, u8 *mac,
				  struct ieee80211_vif *vif)
{
	struct iwl_mvm_stat_data *data = _data;
	struct iwl_mvm *mvm = data->mvm;
	int sig = -data->beacon_filter_average_energy;
	int last_event;
	int thold = vif->bss_conf.cqm_rssi_thold;
	int hyst = vif->bss_conf.cqm_rssi_hyst;
	u16 id = le32_to_cpu(data->mac_id);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u16 vif_id = mvmvif->id;

	/* This doesn't need the MAC ID check since it's not taking the
	 * data copied into the "data" struct, but rather the data from
	 * the notification directly.
	 */
	if (iwl_mvm_has_new_rx_stats_api(mvm)) {
		struct mvm_statistics_general *general =
			data->general;

		mvmvif->beacon_stats.num_beacons =
			le32_to_cpu(general->beacon_counter[vif_id]);
		mvmvif->beacon_stats.avg_signal =
			-general->beacon_average_energy[vif_id];
	} else {
		struct mvm_statistics_general_v8 *general =
			data->general;

		mvmvif->beacon_stats.num_beacons =
			le32_to_cpu(general->beacon_counter[vif_id]);
		mvmvif->beacon_stats.avg_signal =
			-general->beacon_average_energy[vif_id];
	}

	if (mvmvif->id != id)
		return;

	if (vif->type != NL80211_IFTYPE_STATION)
		return;

	if (sig == 0) {
		IWL_DEBUG_RX(mvm, "RSSI is 0 - skip signal based decision\n");
		return;
	}

	mvmvif->bf_data.ave_beacon_signal = sig;

	/* BT Coex */
	if (mvmvif->bf_data.bt_coex_min_thold !=
	    mvmvif->bf_data.bt_coex_max_thold) {
		last_event = mvmvif->bf_data.last_bt_coex_event;
		if (sig > mvmvif->bf_data.bt_coex_max_thold &&
		    (last_event <= mvmvif->bf_data.bt_coex_min_thold ||
		     last_event == 0)) {
			mvmvif->bf_data.last_bt_coex_event = sig;
			IWL_DEBUG_RX(mvm, "cqm_iterator bt coex high %d\n",
				     sig);
			iwl_mvm_bt_rssi_event(mvm, vif, RSSI_EVENT_HIGH);
		} else if (sig < mvmvif->bf_data.bt_coex_min_thold &&
			   (last_event >= mvmvif->bf_data.bt_coex_max_thold ||
			    last_event == 0)) {
			mvmvif->bf_data.last_bt_coex_event = sig;
			IWL_DEBUG_RX(mvm, "cqm_iterator bt coex low %d\n",
				     sig);
			iwl_mvm_bt_rssi_event(mvm, vif, RSSI_EVENT_LOW);
		}
	}

	if (!(vif->driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI))
		return;

	/* CQM Notification */
	last_event = mvmvif->bf_data.last_cqm_event;
	if (thold && sig < thold && (last_event == 0 ||
				     sig < last_event - hyst)) {
		mvmvif->bf_data.last_cqm_event = sig;
		IWL_DEBUG_RX(mvm, "cqm_iterator cqm low %d\n",
			     sig);
		ieee80211_cqm_rssi_notify(
			vif,
			NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
			sig,
			GFP_KERNEL);
	} else if (sig > thold &&
		   (last_event == 0 || sig > last_event + hyst)) {
		mvmvif->bf_data.last_cqm_event = sig;
		IWL_DEBUG_RX(mvm, "cqm_iterator cqm high %d\n",
			     sig);
		ieee80211_cqm_rssi_notify(
			vif,
			NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
			sig,
			GFP_KERNEL);
	}
}