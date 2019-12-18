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
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;

/* Variables and functions */
#define  NL80211_CHAN_WIDTH_10 135 
#define  NL80211_CHAN_WIDTH_160 134 
#define  NL80211_CHAN_WIDTH_20 133 
#define  NL80211_CHAN_WIDTH_20_NOHT 132 
#define  NL80211_CHAN_WIDTH_40 131 
#define  NL80211_CHAN_WIDTH_5 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int QLINK_CHAN_WIDTH_10 ; 
 int QLINK_CHAN_WIDTH_160 ; 
 int QLINK_CHAN_WIDTH_20 ; 
 int QLINK_CHAN_WIDTH_20_NOHT ; 
 int QLINK_CHAN_WIDTH_40 ; 
 int QLINK_CHAN_WIDTH_5 ; 
 int QLINK_CHAN_WIDTH_80 ; 
 int QLINK_CHAN_WIDTH_80P80 ; 

__attribute__((used)) static u8 qlink_chanwidth_nl_to_qlink(enum nl80211_chan_width nlwidth)
{
	switch (nlwidth) {
	case NL80211_CHAN_WIDTH_20_NOHT:
		return QLINK_CHAN_WIDTH_20_NOHT;
	case NL80211_CHAN_WIDTH_20:
		return QLINK_CHAN_WIDTH_20;
	case NL80211_CHAN_WIDTH_40:
		return QLINK_CHAN_WIDTH_40;
	case NL80211_CHAN_WIDTH_80:
		return QLINK_CHAN_WIDTH_80;
	case NL80211_CHAN_WIDTH_80P80:
		return QLINK_CHAN_WIDTH_80P80;
	case NL80211_CHAN_WIDTH_160:
		return QLINK_CHAN_WIDTH_160;
	case NL80211_CHAN_WIDTH_5:
		return QLINK_CHAN_WIDTH_5;
	case NL80211_CHAN_WIDTH_10:
		return QLINK_CHAN_WIDTH_10;
	default:
		return -1;
	}
}