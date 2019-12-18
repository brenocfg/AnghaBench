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

/* Variables and functions */
 int DESC_RATE11M ; 
 int DESC_RATE12M ; 
 int DESC_RATE18M ; 
 int DESC_RATE1M ; 
 int DESC_RATE24M ; 
 int DESC_RATE2M ; 
 int DESC_RATE36M ; 
 int DESC_RATE48M ; 
 int DESC_RATE54M ; 
 int DESC_RATE5_5M ; 
 int DESC_RATE6M ; 
 int DESC_RATE9M ; 
#define  IEEE80211_CCK_RATE_11MB 139 
#define  IEEE80211_CCK_RATE_1MB 138 
#define  IEEE80211_CCK_RATE_2MB 137 
#define  IEEE80211_CCK_RATE_5MB 136 
#define  IEEE80211_OFDM_RATE_12MB 135 
#define  IEEE80211_OFDM_RATE_18MB 134 
#define  IEEE80211_OFDM_RATE_24MB 133 
#define  IEEE80211_OFDM_RATE_36MB 132 
#define  IEEE80211_OFDM_RATE_48MB 131 
#define  IEEE80211_OFDM_RATE_54MB 130 
#define  IEEE80211_OFDM_RATE_6MB 129 
#define  IEEE80211_OFDM_RATE_9MB 128 

u8 MRateToHwRate(u8 rate)
{
	u8 ret = DESC_RATE1M;

	switch (rate) {
		/*  CCK and OFDM non-HT rates */
	case IEEE80211_CCK_RATE_1MB:
		ret = DESC_RATE1M;
		break;
	case IEEE80211_CCK_RATE_2MB:
		ret = DESC_RATE2M;
		break;
	case IEEE80211_CCK_RATE_5MB:
		ret = DESC_RATE5_5M;
		break;
	case IEEE80211_CCK_RATE_11MB:
		ret = DESC_RATE11M;
		break;
	case IEEE80211_OFDM_RATE_6MB:
		ret = DESC_RATE6M;
		break;
	case IEEE80211_OFDM_RATE_9MB:
		ret = DESC_RATE9M;
		break;
	case IEEE80211_OFDM_RATE_12MB:
		ret = DESC_RATE12M;
		break;
	case IEEE80211_OFDM_RATE_18MB:
		ret = DESC_RATE18M;
		break;
	case IEEE80211_OFDM_RATE_24MB:
		ret = DESC_RATE24M;
		break;
	case IEEE80211_OFDM_RATE_36MB:
		ret = DESC_RATE36M;
		break;
	case IEEE80211_OFDM_RATE_48MB:
		ret = DESC_RATE48M;
		break;
	case IEEE80211_OFDM_RATE_54MB:
		ret = DESC_RATE54M;
		break;
	default:
		break;
	}
	return ret;
}