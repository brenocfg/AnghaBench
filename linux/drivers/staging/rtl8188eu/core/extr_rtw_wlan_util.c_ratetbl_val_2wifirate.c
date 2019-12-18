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

/* Variables and functions */
 unsigned char IEEE80211_CCK_RATE_11MB ; 
 unsigned char IEEE80211_CCK_RATE_1MB ; 
 unsigned char IEEE80211_CCK_RATE_2MB ; 
 unsigned char IEEE80211_CCK_RATE_5MB ; 
 unsigned char IEEE80211_OFDM_RATE_12MB ; 
 unsigned char IEEE80211_OFDM_RATE_18MB ; 
 unsigned char IEEE80211_OFDM_RATE_24MB ; 
 unsigned char IEEE80211_OFDM_RATE_36MB ; 
 unsigned char IEEE80211_OFDM_RATE_48MB ; 
 unsigned char IEEE80211_OFDM_RATE_54MB ; 
 unsigned char IEEE80211_OFDM_RATE_6MB ; 
 unsigned char IEEE80211_OFDM_RATE_9MB ; 

__attribute__((used)) static unsigned char ratetbl_val_2wifirate(unsigned char rate)
{
	switch (rate & 0x7f) {
	case 0:
		return IEEE80211_CCK_RATE_1MB;
	case 1:
		return IEEE80211_CCK_RATE_2MB;
	case 2:
		return IEEE80211_CCK_RATE_5MB;
	case 3:
		return IEEE80211_CCK_RATE_11MB;
	case 4:
		return IEEE80211_OFDM_RATE_6MB;
	case 5:
		return IEEE80211_OFDM_RATE_9MB;
	case 6:
		return IEEE80211_OFDM_RATE_12MB;
	case 7:
		return IEEE80211_OFDM_RATE_18MB;
	case 8:
		return IEEE80211_OFDM_RATE_24MB;
	case 9:
		return IEEE80211_OFDM_RATE_36MB;
	case 10:
		return IEEE80211_OFDM_RATE_48MB;
	case 11:
		return IEEE80211_OFDM_RATE_54MB;
	default:
		return 0;
	}
}