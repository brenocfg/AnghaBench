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
typedef  int u32 ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {int plcp; } ;

/* Variables and functions */
 int IL_FIRST_OFDM_RATE ; 
 int NL80211_BAND_5GHZ ; 
 int RATE_COUNT_LEGACY ; 
 int RATE_MCS_HT_MSK ; 
 TYPE_1__* il_rates ; 

int
il4965_hwrate_to_mac80211_idx(u32 rate_n_flags, enum nl80211_band band)
{
	int idx = 0;
	int band_offset = 0;

	/* HT rate format: mac80211 wants an MCS number, which is just LSB */
	if (rate_n_flags & RATE_MCS_HT_MSK) {
		idx = (rate_n_flags & 0xff);
		return idx;
		/* Legacy rate format, search for match in table */
	} else {
		if (band == NL80211_BAND_5GHZ)
			band_offset = IL_FIRST_OFDM_RATE;
		for (idx = band_offset; idx < RATE_COUNT_LEGACY; idx++)
			if (il_rates[idx].plcp == (rate_n_flags & 0xFF))
				return idx - band_offset;
	}

	return -1;
}