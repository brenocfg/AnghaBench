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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int NL80211_VHT_NSS_MAX ; 

__attribute__((used)) static bool
ath10k_peer_assoc_h_vht_masked(const u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
{
	int nss;

	for (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++)
		if (vht_mcs_mask[nss])
			return false;

	return true;
}