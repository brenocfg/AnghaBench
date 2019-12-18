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
typedef  int u32 ;
struct rtw_channel_params {int* cch_by_bw; int center_chan; int bandwidth; int primary_chan_idx; } ;
struct ieee80211_channel {int hw_value; int center_freq; } ;
struct cfg80211_chan_def {int width; int center_freq1; struct ieee80211_channel* chan; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;

/* Variables and functions */
#define  NL80211_CHAN_WIDTH_20 131 
#define  NL80211_CHAN_WIDTH_20_NOHT 130 
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_80 128 
 size_t RTW_CHANNEL_WIDTH_20 ; 
 size_t RTW_CHANNEL_WIDTH_40 ; 
 int RTW_CHANNEL_WIDTH_80 ; 
 int RTW_MAX_CHANNEL_WIDTH ; 

void rtw_get_channel_params(struct cfg80211_chan_def *chandef,
			    struct rtw_channel_params *chan_params)
{
	struct ieee80211_channel *channel = chandef->chan;
	enum nl80211_chan_width width = chandef->width;
	u8 *cch_by_bw = chan_params->cch_by_bw;
	u32 primary_freq, center_freq;
	u8 center_chan;
	u8 bandwidth = RTW_CHANNEL_WIDTH_20;
	u8 primary_chan_idx = 0;
	u8 i;

	center_chan = channel->hw_value;
	primary_freq = channel->center_freq;
	center_freq = chandef->center_freq1;

	/* assign the center channel used while 20M bw is selected */
	cch_by_bw[RTW_CHANNEL_WIDTH_20] = channel->hw_value;

	switch (width) {
	case NL80211_CHAN_WIDTH_20_NOHT:
	case NL80211_CHAN_WIDTH_20:
		bandwidth = RTW_CHANNEL_WIDTH_20;
		primary_chan_idx = 0;
		break;
	case NL80211_CHAN_WIDTH_40:
		bandwidth = RTW_CHANNEL_WIDTH_40;
		if (primary_freq > center_freq) {
			primary_chan_idx = 1;
			center_chan -= 2;
		} else {
			primary_chan_idx = 2;
			center_chan += 2;
		}
		break;
	case NL80211_CHAN_WIDTH_80:
		bandwidth = RTW_CHANNEL_WIDTH_80;
		if (primary_freq > center_freq) {
			if (primary_freq - center_freq == 10) {
				primary_chan_idx = 1;
				center_chan -= 2;
			} else {
				primary_chan_idx = 3;
				center_chan -= 6;
			}
			/* assign the center channel used
			 * while 40M bw is selected
			 */
			cch_by_bw[RTW_CHANNEL_WIDTH_40] = center_chan + 4;
		} else {
			if (center_freq - primary_freq == 10) {
				primary_chan_idx = 2;
				center_chan += 2;
			} else {
				primary_chan_idx = 4;
				center_chan += 6;
			}
			/* assign the center channel used
			 * while 40M bw is selected
			 */
			cch_by_bw[RTW_CHANNEL_WIDTH_40] = center_chan - 4;
		}
		break;
	default:
		center_chan = 0;
		break;
	}

	chan_params->center_chan = center_chan;
	chan_params->bandwidth = bandwidth;
	chan_params->primary_chan_idx = primary_chan_idx;

	/* assign the center channel used while current bw is selected */
	cch_by_bw[bandwidth] = center_chan;

	for (i = bandwidth + 1; i <= RTW_MAX_CHANNEL_WIDTH; i++)
		cch_by_bw[i] = 0;
}