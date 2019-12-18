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
struct ieee80211_vif {int dummy; } ;
struct ath9k_vif_iter_data {int* hw_macaddr; int* mask; } ;

/* Variables and functions */
 int ETH_ALEN ; 

__attribute__((used)) static void ath9k_htc_bssid_iter(void *data, u8 *mac, struct ieee80211_vif *vif)
{
	struct ath9k_vif_iter_data *iter_data = data;
	int i;

	if (iter_data->hw_macaddr != NULL) {
		for (i = 0; i < ETH_ALEN; i++)
			iter_data->mask[i] &= ~(iter_data->hw_macaddr[i] ^ mac[i]);
	} else {
		iter_data->hw_macaddr = mac;
	}
}