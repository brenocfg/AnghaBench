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
struct ieee80211_channel {int /*<<< orphan*/  band; } ;
struct ath5k_hw {int ah_bwmode; struct ieee80211_channel* ah_current_channel; } ;

/* Variables and functions */
#define  AR5K_BWMODE_10MHZ 131 
#define  AR5K_BWMODE_40MHZ 130 
#define  AR5K_BWMODE_5MHZ 129 
#define  AR5K_BWMODE_DEFAULT 128 
 unsigned int AR5K_INIT_SIFS_DEFAULT_A ; 
 unsigned int AR5K_INIT_SIFS_DEFAULT_BG ; 
 unsigned int AR5K_INIT_SIFS_HALF_RATE ; 
 unsigned int AR5K_INIT_SIFS_QUARTER_RATE ; 
 unsigned int AR5K_INIT_SIFS_TURBO ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 

unsigned int
ath5k_hw_get_default_sifs(struct ath5k_hw *ah)
{
	struct ieee80211_channel *channel = ah->ah_current_channel;
	unsigned int sifs;

	switch (ah->ah_bwmode) {
	case AR5K_BWMODE_40MHZ:
		sifs = AR5K_INIT_SIFS_TURBO;
		break;
	case AR5K_BWMODE_10MHZ:
		sifs = AR5K_INIT_SIFS_HALF_RATE;
		break;
	case AR5K_BWMODE_5MHZ:
		sifs = AR5K_INIT_SIFS_QUARTER_RATE;
		break;
	case AR5K_BWMODE_DEFAULT:
	default:
		sifs = AR5K_INIT_SIFS_DEFAULT_BG;
		if (channel->band == NL80211_BAND_5GHZ)
			sifs = AR5K_INIT_SIFS_DEFAULT_A;
		break;
	}

	return sifs;
}