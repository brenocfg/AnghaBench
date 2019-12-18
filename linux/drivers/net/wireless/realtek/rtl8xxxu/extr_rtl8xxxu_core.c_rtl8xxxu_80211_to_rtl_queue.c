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

/* Variables and functions */
#define  IEEE80211_AC_BE 131 
#define  IEEE80211_AC_BK 130 
#define  IEEE80211_AC_VI 129 
#define  IEEE80211_AC_VO 128 
 int TXDESC_QUEUE_BE ; 
 int TXDESC_QUEUE_BK ; 
 int TXDESC_QUEUE_VI ; 
 int TXDESC_QUEUE_VO ; 

__attribute__((used)) static u32 rtl8xxxu_80211_to_rtl_queue(u32 queue)
{
	u32 rtlqueue;

	switch (queue) {
	case IEEE80211_AC_VO:
		rtlqueue = TXDESC_QUEUE_VO;
		break;
	case IEEE80211_AC_VI:
		rtlqueue = TXDESC_QUEUE_VI;
		break;
	case IEEE80211_AC_BE:
		rtlqueue = TXDESC_QUEUE_BE;
		break;
	case IEEE80211_AC_BK:
		rtlqueue = TXDESC_QUEUE_BK;
		break;
	default:
		rtlqueue = TXDESC_QUEUE_BE;
	}

	return rtlqueue;
}