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
struct ieee80211_sta {int* supp_rates; } ;

/* Variables and functions */
 int ATH10K_MAC_FIRST_OFDM_RATE_IDX ; 
 size_t NL80211_BAND_2GHZ ; 

__attribute__((used)) static bool ath10k_mac_sta_has_ofdm_only(struct ieee80211_sta *sta)
{
	return sta->supp_rates[NL80211_BAND_2GHZ] >>
	       ATH10K_MAC_FIRST_OFDM_RATE_IDX;
}