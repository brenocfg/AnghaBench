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
typedef  int u32 ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int type; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  idle; } ;

/* Variables and functions */
 int BSS_CHANGED_IDLE ; 
 int BSS_CHANGED_MU_GROUPS ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_SCAN_SCHED ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_mvm_bss_info_changed_ap_ibss (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_bss_conf*,int) ; 
 int /*<<< orphan*/  iwl_mvm_bss_info_changed_station (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_bss_conf*,int) ; 
 int /*<<< orphan*/  iwl_mvm_scan_stop (struct iwl_mvm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_mvm_update_mu_groups (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_bss_info_changed(struct ieee80211_hw *hw,
				     struct ieee80211_vif *vif,
				     struct ieee80211_bss_conf *bss_conf,
				     u32 changes)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);

	if (changes & BSS_CHANGED_IDLE && !bss_conf->idle)
		iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_SCHED, true);

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		iwl_mvm_bss_info_changed_station(mvm, vif, bss_conf, changes);
		break;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_ADHOC:
		iwl_mvm_bss_info_changed_ap_ibss(mvm, vif, bss_conf, changes);
		break;
	case NL80211_IFTYPE_MONITOR:
		if (changes & BSS_CHANGED_MU_GROUPS)
			iwl_mvm_update_mu_groups(mvm, vif);
		break;
	default:
		/* shouldn't happen */
		WARN_ON_ONCE(1);
	}

	mutex_unlock(&mvm->mutex);
}