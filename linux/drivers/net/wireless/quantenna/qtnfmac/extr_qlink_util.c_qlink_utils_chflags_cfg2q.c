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
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_160MHZ ; 
 int IEEE80211_CHAN_NO_80MHZ ; 
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 int QLINK_CHAN_DISABLED ; 
 int QLINK_CHAN_NO_160MHZ ; 
 int QLINK_CHAN_NO_80MHZ ; 
 int QLINK_CHAN_NO_HT40MINUS ; 
 int QLINK_CHAN_NO_HT40PLUS ; 
 int QLINK_CHAN_NO_IR ; 
 int QLINK_CHAN_RADAR ; 

u32 qlink_utils_chflags_cfg2q(u32 cfgflags)
{
	u32 flags = 0;

	if (cfgflags & IEEE80211_CHAN_DISABLED)
		flags |= QLINK_CHAN_DISABLED;

	if (cfgflags & IEEE80211_CHAN_NO_IR)
		flags |= QLINK_CHAN_NO_IR;

	if (cfgflags & IEEE80211_CHAN_RADAR)
		flags |= QLINK_CHAN_RADAR;

	if (cfgflags & IEEE80211_CHAN_NO_HT40PLUS)
		flags |= QLINK_CHAN_NO_HT40PLUS;

	if (cfgflags & IEEE80211_CHAN_NO_HT40MINUS)
		flags |= QLINK_CHAN_NO_HT40MINUS;

	if (cfgflags & IEEE80211_CHAN_NO_80MHZ)
		flags |= QLINK_CHAN_NO_80MHZ;

	if (cfgflags & IEEE80211_CHAN_NO_160MHZ)
		flags |= QLINK_CHAN_NO_160MHZ;

	return flags;
}