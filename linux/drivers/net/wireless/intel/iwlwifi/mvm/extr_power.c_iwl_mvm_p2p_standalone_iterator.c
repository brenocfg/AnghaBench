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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  assoc; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 int ieee80211_vif_type_p2p (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_p2p_standalone_iterator(void *_data, u8 *mac,
					    struct ieee80211_vif *vif)
{
	bool *is_p2p_standalone = _data;

	switch (ieee80211_vif_type_p2p(vif)) {
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_AP:
		*is_p2p_standalone = false;
		break;
	case NL80211_IFTYPE_STATION:
		if (vif->bss_conf.assoc)
			*is_p2p_standalone = false;
		break;

	default:
		break;
	}
}