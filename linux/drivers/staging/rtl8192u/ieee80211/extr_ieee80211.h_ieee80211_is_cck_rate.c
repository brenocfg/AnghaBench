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
 int IEEE80211_BASIC_RATE_MASK ; 
#define  IEEE80211_CCK_RATE_11MB 131 
#define  IEEE80211_CCK_RATE_1MB 130 
#define  IEEE80211_CCK_RATE_2MB 129 
#define  IEEE80211_CCK_RATE_5MB 128 

__attribute__((used)) static inline int ieee80211_is_cck_rate(u8 rate)
{
	switch (rate & ~IEEE80211_BASIC_RATE_MASK) {
	case IEEE80211_CCK_RATE_1MB:
	case IEEE80211_CCK_RATE_2MB:
	case IEEE80211_CCK_RATE_5MB:
	case IEEE80211_CCK_RATE_11MB:
		return 1;
	}
	return 0;
}