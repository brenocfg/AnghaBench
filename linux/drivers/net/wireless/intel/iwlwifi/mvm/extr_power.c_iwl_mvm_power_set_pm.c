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
struct iwl_power_vifs {scalar_t__ ap_active; scalar_t__ p2p_active; scalar_t__ bss_active; scalar_t__ ap_vif; scalar_t__ p2p_vif; scalar_t__ bss_vif; } ;
struct iwl_mvm_vif {int pm_enabled; TYPE_1__* phy_ctxt; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_power_disable_pm_iterator ; 
 scalar_t__ iwl_mvm_tdls_sta_count (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_power_set_pm(struct iwl_mvm *mvm,
				 struct iwl_power_vifs *vifs)
{
	struct iwl_mvm_vif *bss_mvmvif = NULL;
	struct iwl_mvm_vif *p2p_mvmvif = NULL;
	struct iwl_mvm_vif *ap_mvmvif = NULL;
	bool client_same_channel = false;
	bool ap_same_channel = false;

	lockdep_assert_held(&mvm->mutex);

	/* set pm_enable to false */
	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_power_disable_pm_iterator,
					NULL);

	if (vifs->bss_vif)
		bss_mvmvif = iwl_mvm_vif_from_mac80211(vifs->bss_vif);

	if (vifs->p2p_vif)
		p2p_mvmvif = iwl_mvm_vif_from_mac80211(vifs->p2p_vif);

	if (vifs->ap_vif)
		ap_mvmvif = iwl_mvm_vif_from_mac80211(vifs->ap_vif);

	/* don't allow PM if any TDLS stations exist */
	if (iwl_mvm_tdls_sta_count(mvm, NULL))
		return;

	/* enable PM on bss if bss stand alone */
	if (vifs->bss_active && !vifs->p2p_active && !vifs->ap_active) {
		bss_mvmvif->pm_enabled = true;
		return;
	}

	/* enable PM on p2p if p2p stand alone */
	if (vifs->p2p_active && !vifs->bss_active && !vifs->ap_active) {
		p2p_mvmvif->pm_enabled = true;
		return;
	}

	if (vifs->bss_active && vifs->p2p_active)
		client_same_channel = (bss_mvmvif->phy_ctxt->id ==
				       p2p_mvmvif->phy_ctxt->id);
	if (vifs->bss_active && vifs->ap_active)
		ap_same_channel = (bss_mvmvif->phy_ctxt->id ==
				   ap_mvmvif->phy_ctxt->id);

	/* clients are not stand alone: enable PM if DCM */
	if (!(client_same_channel || ap_same_channel)) {
		if (vifs->bss_active)
			bss_mvmvif->pm_enabled = true;
		if (vifs->p2p_active)
			p2p_mvmvif->pm_enabled = true;
		return;
	}

	/*
	 * There is only one channel in the system and there are only
	 * bss and p2p clients that share it
	 */
	if (client_same_channel && !vifs->ap_active) {
		/* share same channel*/
		bss_mvmvif->pm_enabled = true;
		p2p_mvmvif->pm_enabled = true;
	}
}