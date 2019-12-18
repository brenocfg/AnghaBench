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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int dtim_period; int beacon_int; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  iwl_mvm_protect_session (struct iwl_mvm*,struct ieee80211_vif*,int,int,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void iwl_mvm_mac_mgd_protect_tdls_discover(struct ieee80211_hw *hw,
					   struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	u32 duration = 2 * vif->bss_conf.dtim_period * vif->bss_conf.beacon_int;

	mutex_lock(&mvm->mutex);
	/* Protect the session to hear the TDLS setup response on the channel */
	iwl_mvm_protect_session(mvm, vif, duration, duration, 100, true);
	mutex_unlock(&mvm->mutex);
}