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
struct iwl_time_event_notif {int /*<<< orphan*/  status; } ;
struct iwl_mvm_vif {int csa_failed; int /*<<< orphan*/  csa_work; } ;
struct iwl_mvm_time_event_data {struct ieee80211_vif* vif; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TE (struct iwl_mvm*,char*) ; 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_chswitch_done (struct ieee80211_vif*,int) ; 
 int /*<<< orphan*/  iwl_mvm_connection_loss (struct iwl_mvm*,struct ieee80211_vif*,char*) ; 
 int /*<<< orphan*/  iwl_mvm_csa_client_absent (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_csa_noa_start (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_te_clear_data (struct iwl_mvm*,struct iwl_mvm_time_event_data*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void
iwl_mvm_te_handle_notify_csa(struct iwl_mvm *mvm,
			     struct iwl_mvm_time_event_data *te_data,
			     struct iwl_time_event_notif *notif)
{
	struct ieee80211_vif *vif = te_data->vif;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	if (!notif->status)
		IWL_DEBUG_TE(mvm, "CSA time event failed to start\n");

	switch (te_data->vif->type) {
	case NL80211_IFTYPE_AP:
		if (!notif->status)
			mvmvif->csa_failed = true;
		iwl_mvm_csa_noa_start(mvm);
		break;
	case NL80211_IFTYPE_STATION:
		if (!notif->status) {
			iwl_mvm_connection_loss(mvm, vif,
						"CSA TE failed to start");
			break;
		}
		iwl_mvm_csa_client_absent(mvm, te_data->vif);
		cancel_delayed_work(&mvmvif->csa_work);
		ieee80211_chswitch_done(te_data->vif, true);
		break;
	default:
		/* should never happen */
		WARN_ON_ONCE(1);
		break;
	}

	/* we don't need it anymore */
	iwl_mvm_te_clear_data(mvm, te_data);
}