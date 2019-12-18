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
struct iwl_mvm_sta {int /*<<< orphan*/  sta_id; int /*<<< orphan*/  vif; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,int /*<<< orphan*/ ) ; 
 int ieee80211_vif_type_p2p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_bfer_priority(struct iwl_mvm_sta *sta)
{
	int prio = -1;
	enum nl80211_iftype viftype = ieee80211_vif_type_p2p(sta->vif);

	switch (viftype) {
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_P2P_GO:
		prio = 3;
		break;
	case NL80211_IFTYPE_P2P_CLIENT:
		prio = 2;
		break;
	case NL80211_IFTYPE_STATION:
		prio = 1;
		break;
	default:
		WARN_ONCE(true, "viftype %d sta_id %d", viftype, sta->sta_id);
		prio = -1;
	}

	return prio;
}