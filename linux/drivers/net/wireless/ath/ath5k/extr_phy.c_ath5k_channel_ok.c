#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct ieee80211_channel {scalar_t__ center_freq; scalar_t__ band; } ;
struct TYPE_3__ {scalar_t__ range_2ghz_min; scalar_t__ range_2ghz_max; scalar_t__ range_5ghz_min; scalar_t__ range_5ghz_max; } ;
struct TYPE_4__ {TYPE_1__ cap_range; } ;
struct ath5k_hw {TYPE_2__ ah_capabilities; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 

bool
ath5k_channel_ok(struct ath5k_hw *ah, struct ieee80211_channel *channel)
{
	u16 freq = channel->center_freq;

	/* Check if the channel is in our supported range */
	if (channel->band == NL80211_BAND_2GHZ) {
		if ((freq >= ah->ah_capabilities.cap_range.range_2ghz_min) &&
		    (freq <= ah->ah_capabilities.cap_range.range_2ghz_max))
			return true;
	} else if (channel->band == NL80211_BAND_5GHZ)
		if ((freq >= ah->ah_capabilities.cap_range.range_5ghz_min) &&
		    (freq <= ah->ah_capabilities.cap_range.range_5ghz_max))
			return true;

	return false;
}