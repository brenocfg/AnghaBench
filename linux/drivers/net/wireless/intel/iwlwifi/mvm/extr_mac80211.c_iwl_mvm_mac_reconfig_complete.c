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
struct iwl_mvm {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ieee80211_reconfig_type { ____Placeholder_ieee80211_reconfig_type } ieee80211_reconfig_type ;

/* Variables and functions */
#define  IEEE80211_RECONFIG_TYPE_RESTART 129 
#define  IEEE80211_RECONFIG_TYPE_SUSPEND 128 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  iwl_mvm_restart_complete (struct iwl_mvm*) ; 

__attribute__((used)) static void
iwl_mvm_mac_reconfig_complete(struct ieee80211_hw *hw,
			      enum ieee80211_reconfig_type reconfig_type)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	switch (reconfig_type) {
	case IEEE80211_RECONFIG_TYPE_RESTART:
		iwl_mvm_restart_complete(mvm);
		break;
	case IEEE80211_RECONFIG_TYPE_SUSPEND:
		break;
	}
}