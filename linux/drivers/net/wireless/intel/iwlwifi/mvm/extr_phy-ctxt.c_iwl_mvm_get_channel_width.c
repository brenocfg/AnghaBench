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
typedef  int /*<<< orphan*/  u8 ;
struct cfg80211_chan_def {int width; } ;

/* Variables and functions */
#define  NL80211_CHAN_WIDTH_160 132 
#define  NL80211_CHAN_WIDTH_20 131 
#define  NL80211_CHAN_WIDTH_20_NOHT 130 
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_80 128 
 int /*<<< orphan*/  PHY_VHT_CHANNEL_MODE160 ; 
 int /*<<< orphan*/  PHY_VHT_CHANNEL_MODE20 ; 
 int /*<<< orphan*/  PHY_VHT_CHANNEL_MODE40 ; 
 int /*<<< orphan*/  PHY_VHT_CHANNEL_MODE80 ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 

u8 iwl_mvm_get_channel_width(struct cfg80211_chan_def *chandef)
{
	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_20_NOHT:
	case NL80211_CHAN_WIDTH_20:
		return PHY_VHT_CHANNEL_MODE20;
	case NL80211_CHAN_WIDTH_40:
		return PHY_VHT_CHANNEL_MODE40;
	case NL80211_CHAN_WIDTH_80:
		return PHY_VHT_CHANNEL_MODE80;
	case NL80211_CHAN_WIDTH_160:
		return PHY_VHT_CHANNEL_MODE160;
	default:
		WARN(1, "Invalid channel width=%u", chandef->width);
		return PHY_VHT_CHANNEL_MODE20;
	}
}