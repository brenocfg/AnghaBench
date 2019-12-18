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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  enable_beacon; int /*<<< orphan*/  use_short_slot; } ;
struct ieee80211_vif {int type; TYPE_1__ bss_conf; scalar_t__ drv_priv; } ;
struct ath_vif {int /*<<< orphan*/  assoc; } ;
struct ath9k_vif_iter_data {int has_hw_macaddr; int* mask; int* hw_macaddr; int slottime; int /*<<< orphan*/  nwds; int /*<<< orphan*/  nmeshes; int /*<<< orphan*/  nadhocs; int /*<<< orphan*/  nocbs; struct ieee80211_vif* primary_sta; int /*<<< orphan*/  nstations; int /*<<< orphan*/  naps; } ;

/* Variables and functions */
 int ETH_ALEN ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_MESH_POINT 131 
#define  NL80211_IFTYPE_OCB 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int /*<<< orphan*/  ath9k_vif_iter_set_beacon (struct ath9k_vif_iter_data*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void ath9k_vif_iter(struct ath9k_vif_iter_data *iter_data,
			   u8 *mac, struct ieee80211_vif *vif)
{
	struct ath_vif *avp = (struct ath_vif *)vif->drv_priv;
	int i;

	if (iter_data->has_hw_macaddr) {
		for (i = 0; i < ETH_ALEN; i++)
			iter_data->mask[i] &=
				~(iter_data->hw_macaddr[i] ^ mac[i]);
	} else {
		memcpy(iter_data->hw_macaddr, mac, ETH_ALEN);
		iter_data->has_hw_macaddr = true;
	}

	if (!vif->bss_conf.use_short_slot)
		iter_data->slottime = 20;

	switch (vif->type) {
	case NL80211_IFTYPE_AP:
		iter_data->naps++;
		if (vif->bss_conf.enable_beacon)
			ath9k_vif_iter_set_beacon(iter_data, vif);
		break;
	case NL80211_IFTYPE_STATION:
		iter_data->nstations++;
		if (avp->assoc && !iter_data->primary_sta)
			iter_data->primary_sta = vif;
		break;
	case NL80211_IFTYPE_OCB:
		iter_data->nocbs++;
		break;
	case NL80211_IFTYPE_ADHOC:
		iter_data->nadhocs++;
		if (vif->bss_conf.enable_beacon)
			ath9k_vif_iter_set_beacon(iter_data, vif);
		break;
	case NL80211_IFTYPE_MESH_POINT:
		iter_data->nmeshes++;
		if (vif->bss_conf.enable_beacon)
			ath9k_vif_iter_set_beacon(iter_data, vif);
		break;
	case NL80211_IFTYPE_WDS:
		iter_data->nwds++;
		break;
	default:
		break;
	}
}