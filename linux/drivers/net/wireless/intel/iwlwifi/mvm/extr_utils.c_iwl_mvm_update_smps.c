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
struct iwl_mvm_vif {int* smps_requests; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {scalar_t__ type; } ;
typedef  enum iwl_mvm_smps_type_request { ____Placeholder_iwl_mvm_smps_type_request } iwl_mvm_smps_type_request ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
 int IEEE80211_SMPS_AUTOMATIC ; 
 scalar_t__ IEEE80211_SMPS_DYNAMIC ; 
 int IEEE80211_SMPS_OFF ; 
 scalar_t__ IEEE80211_SMPS_STATIC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int NUM_IWL_MVM_SMPS_REQ ; 
 int /*<<< orphan*/  ieee80211_request_smps (struct ieee80211_vif*,int) ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_rx_ant (struct iwl_mvm*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int num_of_ant (int /*<<< orphan*/ ) ; 

void iwl_mvm_update_smps(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			 enum iwl_mvm_smps_type_request req_type,
			 enum ieee80211_smps_mode smps_request)
{
	struct iwl_mvm_vif *mvmvif;
	enum ieee80211_smps_mode smps_mode;
	int i;

	lockdep_assert_held(&mvm->mutex);

	/* SMPS is irrelevant for NICs that don't have at least 2 RX antenna */
	if (num_of_ant(iwl_mvm_get_valid_rx_ant(mvm)) == 1)
		return;

	if (vif->type == NL80211_IFTYPE_AP)
		smps_mode = IEEE80211_SMPS_OFF;
	else
		smps_mode = IEEE80211_SMPS_AUTOMATIC;

	mvmvif = iwl_mvm_vif_from_mac80211(vif);
	mvmvif->smps_requests[req_type] = smps_request;
	for (i = 0; i < NUM_IWL_MVM_SMPS_REQ; i++) {
		if (mvmvif->smps_requests[i] == IEEE80211_SMPS_STATIC) {
			smps_mode = IEEE80211_SMPS_STATIC;
			break;
		}
		if (mvmvif->smps_requests[i] == IEEE80211_SMPS_DYNAMIC)
			smps_mode = IEEE80211_SMPS_DYNAMIC;
	}

	ieee80211_request_smps(vif, smps_mode);
}