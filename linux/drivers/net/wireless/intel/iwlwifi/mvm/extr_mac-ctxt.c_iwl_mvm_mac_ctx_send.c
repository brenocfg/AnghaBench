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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int type; int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MONITOR 130 
#define  NL80211_IFTYPE_P2P_DEVICE 129 
#define  NL80211_IFTYPE_STATION 128 
 int iwl_mvm_mac_ctxt_cmd_ap (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_cmd_go (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_cmd_ibss (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_cmd_listener (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_cmd_p2p_device (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_cmd_sta (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int iwl_mvm_mac_ctx_send(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
				u32 action, bool force_assoc_off,
				const u8 *bssid_override)
{
	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		return iwl_mvm_mac_ctxt_cmd_sta(mvm, vif, action,
						force_assoc_off,
						bssid_override);
		break;
	case NL80211_IFTYPE_AP:
		if (!vif->p2p)
			return iwl_mvm_mac_ctxt_cmd_ap(mvm, vif, action);
		else
			return iwl_mvm_mac_ctxt_cmd_go(mvm, vif, action);
		break;
	case NL80211_IFTYPE_MONITOR:
		return iwl_mvm_mac_ctxt_cmd_listener(mvm, vif, action);
	case NL80211_IFTYPE_P2P_DEVICE:
		return iwl_mvm_mac_ctxt_cmd_p2p_device(mvm, vif, action);
	case NL80211_IFTYPE_ADHOC:
		return iwl_mvm_mac_ctxt_cmd_ibss(mvm, vif, action);
	default:
		break;
	}

	return -EOPNOTSUPP;
}