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
typedef  int u16 ;
struct ieee80211_channel {scalar_t__ band; int /*<<< orphan*/  center_freq; } ;
struct cfg80211_chan_def {int width; struct ieee80211_channel* chan; int /*<<< orphan*/  center_freq1; } ;
struct ath9k_channel {int channelFlags; struct ieee80211_channel* chan; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int CHANNEL_5GHZ ; 
 int CHANNEL_HALF ; 
 int CHANNEL_HT ; 
 int CHANNEL_HT40MINUS ; 
 int CHANNEL_HT40PLUS ; 
 int CHANNEL_QUARTER ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
#define  NL80211_CHAN_WIDTH_10 132 
#define  NL80211_CHAN_WIDTH_20 131 
#define  NL80211_CHAN_WIDTH_20_NOHT 130 
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_5 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void ath9k_cmn_update_ichannel(struct ath9k_channel *ichan,
				      struct cfg80211_chan_def *chandef)
{
	struct ieee80211_channel *chan = chandef->chan;
	u16 flags = 0;

	ichan->channel = chan->center_freq;
	ichan->chan = chan;

	if (chan->band == NL80211_BAND_5GHZ)
		flags |= CHANNEL_5GHZ;

	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_5:
		flags |= CHANNEL_QUARTER;
		break;
	case NL80211_CHAN_WIDTH_10:
		flags |= CHANNEL_HALF;
		break;
	case NL80211_CHAN_WIDTH_20_NOHT:
		break;
	case NL80211_CHAN_WIDTH_20:
		flags |= CHANNEL_HT;
		break;
	case NL80211_CHAN_WIDTH_40:
		if (chandef->center_freq1 > chandef->chan->center_freq)
			flags |= CHANNEL_HT40PLUS | CHANNEL_HT;
		else
			flags |= CHANNEL_HT40MINUS | CHANNEL_HT;
		break;
	default:
		WARN_ON(1);
	}

	ichan->channelFlags = flags;
}