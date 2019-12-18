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
typedef  int u8 ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ath5k_vif_iter_data {int* hw_macaddr; int* mask; int found_active; int need_set_hw_addr; int any_assoc; scalar_t__ opmode; int /*<<< orphan*/  n_stas; int /*<<< orphan*/  active_mac; } ;
struct ath5k_vif {scalar_t__ opmode; scalar_t__ assoc; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 scalar_t__ ether_addr_equal (int*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

void ath5k_vif_iter(void *data, u8 *mac, struct ieee80211_vif *vif)
{
	struct ath5k_vif_iter_data *iter_data = data;
	int i;
	struct ath5k_vif *avf = (void *)vif->drv_priv;

	if (iter_data->hw_macaddr)
		for (i = 0; i < ETH_ALEN; i++)
			iter_data->mask[i] &=
				~(iter_data->hw_macaddr[i] ^ mac[i]);

	if (!iter_data->found_active) {
		iter_data->found_active = true;
		memcpy(iter_data->active_mac, mac, ETH_ALEN);
	}

	if (iter_data->need_set_hw_addr && iter_data->hw_macaddr)
		if (ether_addr_equal(iter_data->hw_macaddr, mac))
			iter_data->need_set_hw_addr = false;

	if (!iter_data->any_assoc) {
		if (avf->assoc)
			iter_data->any_assoc = true;
	}

	/* Calculate combined mode - when APs are active, operate in AP mode.
	 * Otherwise use the mode of the new interface. This can currently
	 * only deal with combinations of APs and STAs. Only one ad-hoc
	 * interfaces is allowed.
	 */
	if (avf->opmode == NL80211_IFTYPE_AP)
		iter_data->opmode = NL80211_IFTYPE_AP;
	else {
		if (avf->opmode == NL80211_IFTYPE_STATION)
			iter_data->n_stas++;
		if (iter_data->opmode == NL80211_IFTYPE_UNSPECIFIED)
			iter_data->opmode = avf->opmode;
	}
}