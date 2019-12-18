#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct mlme_ext_priv {unsigned int max_chan_nums; TYPE_1__* channel_set; } ;
struct ieee80211_supported_band {unsigned int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_channel {scalar_t__ flags; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_2__ {scalar_t__ ScanType; int /*<<< orphan*/  ChannelNum; } ;
typedef  TYPE_1__ RT_CHANNEL_INFO ;

/* Variables and functions */
 scalar_t__ IEEE80211_CHAN_DISABLED ; 
 scalar_t__ IEEE80211_CHAN_NO_IR ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 unsigned int NUM_NL80211_BANDS ; 
 scalar_t__ SCAN_PASSIVE ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adapter* wiphy_to_adapter (struct wiphy*) ; 

__attribute__((used)) static void _rtw_reg_apply_flags(struct wiphy *wiphy)
{
	struct adapter *padapter = wiphy_to_adapter(wiphy);
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	RT_CHANNEL_INFO *channel_set = pmlmeext->channel_set;
	u8 max_chan_nums = pmlmeext->max_chan_nums;

	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *ch;
	unsigned int i, j;
	u16 channel;
	u32 freq;

	/* all channels disable */
	for (i = 0; i < NUM_NL80211_BANDS; i++) {
		sband = wiphy->bands[i];

		if (sband) {
			for (j = 0; j < sband->n_channels; j++) {
				ch = &sband->channels[j];

				if (ch)
					ch->flags = IEEE80211_CHAN_DISABLED;
			}
		}
	}

	/* channels apply by channel plans. */
	for (i = 0; i < max_chan_nums; i++) {
		channel = channel_set[i].ChannelNum;
		freq =
		    rtw_ieee80211_channel_to_frequency(channel,
						       NL80211_BAND_2GHZ);

		ch = ieee80211_get_channel(wiphy, freq);
		if (ch) {
			if (channel_set[i].ScanType == SCAN_PASSIVE)
				ch->flags = IEEE80211_CHAN_NO_IR;
			else
				ch->flags = 0;
		}
	}
}