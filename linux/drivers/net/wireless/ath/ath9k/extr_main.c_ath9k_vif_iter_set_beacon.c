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
struct ieee80211_vif {scalar_t__ type; } ;
struct ath9k_vif_iter_data {int beacons; int nbcnvifs; struct ieee80211_vif* primary_beacon_vif; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 

__attribute__((used)) static void ath9k_vif_iter_set_beacon(struct ath9k_vif_iter_data *iter_data,
				      struct ieee80211_vif *vif)
{
	/* Use the first (configured) interface, but prefering AP interfaces. */
	if (!iter_data->primary_beacon_vif) {
		iter_data->primary_beacon_vif = vif;
	} else {
		if (iter_data->primary_beacon_vif->type != NL80211_IFTYPE_AP &&
		    vif->type == NL80211_IFTYPE_AP)
			iter_data->primary_beacon_vif = vif;
	}

	iter_data->beacons = true;
	iter_data->nbcnvifs += 1;
}