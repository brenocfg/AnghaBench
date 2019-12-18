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
typedef  int u32 ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int IWL_FIRST_OFDM_RATE ; 
 int IWL_RATE_COUNT_LEGACY ; 
 int NL80211_BAND_5GHZ ; 
 int RATE_LEGACY_RATE_MSK ; 
 int* fw_rate_idx_to_plcp ; 

int iwl_mvm_legacy_rate_to_mac80211_idx(u32 rate_n_flags,
					enum nl80211_band band)
{
	int rate = rate_n_flags & RATE_LEGACY_RATE_MSK;
	int idx;
	int band_offset = 0;

	/* Legacy rate format, search for match in table */
	if (band == NL80211_BAND_5GHZ)
		band_offset = IWL_FIRST_OFDM_RATE;
	for (idx = band_offset; idx < IWL_RATE_COUNT_LEGACY; idx++)
		if (fw_rate_idx_to_plcp[idx] == rate)
			return idx - band_offset;

	return -1;
}