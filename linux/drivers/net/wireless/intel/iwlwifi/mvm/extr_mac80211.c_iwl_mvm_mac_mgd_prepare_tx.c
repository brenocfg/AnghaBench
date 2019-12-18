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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_MVM_TE_SESSION_PROTECTION_MAX_TIME_MS ; 
 scalar_t__ IWL_MVM_TE_SESSION_PROTECTION_MIN_TIME_MS ; 
 int /*<<< orphan*/  iwl_mvm_protect_session (struct iwl_mvm*,struct ieee80211_vif*,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_mgd_prepare_tx(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif,
				       u16 req_duration)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	u32 duration = IWL_MVM_TE_SESSION_PROTECTION_MAX_TIME_MS;
	u32 min_duration = IWL_MVM_TE_SESSION_PROTECTION_MIN_TIME_MS;

	if (req_duration > duration)
		duration = req_duration;

	mutex_lock(&mvm->mutex);
	/* Try really hard to protect the session and hear a beacon */
	iwl_mvm_protect_session(mvm, vif, duration, min_duration, 500, false);
	mutex_unlock(&mvm->mutex);
}