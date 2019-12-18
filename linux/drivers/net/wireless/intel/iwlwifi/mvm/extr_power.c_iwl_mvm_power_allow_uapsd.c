#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm_vif {int /*<<< orphan*/  uapsd_misbehaving_bssid; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int oppps_ctwindow; } ;
struct TYPE_4__ {TYPE_1__ p2p_noa_attr; int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {scalar_t__ p2p; TYPE_2__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int IEEE80211_P2P_OPPPS_ENABLE_BIT ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  iwl_mvm_is_p2p_scm_uapsd_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_p2p_standalone_iterator ; 
 int iwl_mvm_phy_ctx_count (struct iwl_mvm*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool iwl_mvm_power_allow_uapsd(struct iwl_mvm *mvm,
				       struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	if (!memcmp(mvmvif->uapsd_misbehaving_bssid, vif->bss_conf.bssid,
		    ETH_ALEN))
		return false;

	/*
	 * Avoid using uAPSD if P2P client is associated to GO that uses
	 * opportunistic power save. This is due to current FW limitation.
	 */
	if (vif->p2p &&
	    (vif->bss_conf.p2p_noa_attr.oppps_ctwindow &
	    IEEE80211_P2P_OPPPS_ENABLE_BIT))
		return false;

	/*
	 * Avoid using uAPSD if client is in DCM -
	 * low latency issue in Miracast
	 */
	if (iwl_mvm_phy_ctx_count(mvm) >= 2)
		return false;

	if (vif->p2p) {
		/* Allow U-APSD only if p2p is stand alone */
		bool is_p2p_standalone = true;

		if (!iwl_mvm_is_p2p_scm_uapsd_supported(mvm))
			return false;

		ieee80211_iterate_active_interfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_p2p_standalone_iterator,
					&is_p2p_standalone);

		if (!is_p2p_standalone)
			return false;
	}

	return true;
}