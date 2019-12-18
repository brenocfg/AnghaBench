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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IEEE80211_AC_BE ; 
 int IEEE80211_AC_BK ; 
 int IEEE80211_AC_VI ; 
 int IEEE80211_AC_VO ; 

__attribute__((used)) static int mwl8k_tid_queue_mapping(u8 tid)
{
	BUG_ON(tid > 7);

	switch (tid) {
	case 0:
	case 3:
		return IEEE80211_AC_BE;
	case 1:
	case 2:
		return IEEE80211_AC_BK;
	case 4:
	case 5:
		return IEEE80211_AC_VI;
	case 6:
	case 7:
		return IEEE80211_AC_VO;
	default:
		return -1;
	}
}