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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {scalar_t__ type; int /*<<< orphan*/  p2p; TYPE_1__ bss_conf; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 unsigned int FIF_PROBE_REQ ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_config_iface_filter(struct ieee80211_hw *hw,
					struct ieee80211_vif *vif,
					unsigned int filter_flags,
					unsigned int changed_flags)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	/* We support only filter for probe requests */
	if (!(changed_flags & FIF_PROBE_REQ))
		return;

	/* Supported only for p2p client interfaces */
	if (vif->type != NL80211_IFTYPE_STATION || !vif->bss_conf.assoc ||
	    !vif->p2p)
		return;

	mutex_lock(&mvm->mutex);
	iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);
	mutex_unlock(&mvm->mutex);
}