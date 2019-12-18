#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct rsi_hw {scalar_t__ device_model; struct ieee80211_hw* hw; } ;
struct rsi_common {scalar_t__ channel_width; scalar_t__ endpoint; scalar_t__ band; int rf_reset; struct rsi_hw* priv; } ;
struct TYPE_3__ {scalar_t__ width; } ;
struct TYPE_4__ {TYPE_1__ chandef; } ;
struct ieee80211_hw {TYPE_2__ conf; } ;
struct ieee80211_channel {scalar_t__ band; } ;

/* Variables and functions */
 scalar_t__ BW_20MHZ ; 
 scalar_t__ BW_40MHZ ; 
 scalar_t__ EP_2GHZ_20MHZ ; 
 scalar_t__ EP_2GHZ_40MHZ ; 
 scalar_t__ EP_5GHZ_20MHZ ; 
 scalar_t__ EP_5GHZ_40MHZ ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_CHAN_WIDTH_20 ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 scalar_t__ RSI_DEV_9116 ; 
 int rsi_load_9116_bootup_params (struct rsi_common*) ; 
 int rsi_load_bootup_params (struct rsi_common*) ; 
 int rsi_load_radio_caps (struct rsi_common*) ; 
 int rsi_program_bb_rf (struct rsi_common*) ; 

int rsi_band_check(struct rsi_common *common,
		   struct ieee80211_channel *curchan)
{
	struct rsi_hw *adapter = common->priv;
	struct ieee80211_hw *hw = adapter->hw;
	u8 prev_bw = common->channel_width;
	u8 prev_ep = common->endpoint;
	int status = 0;

	if (common->band != curchan->band) {
		common->rf_reset = 1;
		common->band = curchan->band;
	}

	if ((hw->conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT) ||
	    (hw->conf.chandef.width == NL80211_CHAN_WIDTH_20))
		common->channel_width = BW_20MHZ;
	else
		common->channel_width = BW_40MHZ;

	if (common->band == NL80211_BAND_2GHZ) {
		if (common->channel_width)
			common->endpoint = EP_2GHZ_40MHZ;
		else
			common->endpoint = EP_2GHZ_20MHZ;
	} else {
		if (common->channel_width)
			common->endpoint = EP_5GHZ_40MHZ;
		else
			common->endpoint = EP_5GHZ_20MHZ;
	}

	if (common->endpoint != prev_ep) {
		status = rsi_program_bb_rf(common);
		if (status)
			return status;
	}

	if (common->channel_width != prev_bw) {
		if (adapter->device_model == RSI_DEV_9116)
			status = rsi_load_9116_bootup_params(common);
		else
			status = rsi_load_bootup_params(common);
		if (status)
			return status;

		status = rsi_load_radio_caps(common);
		if (status)
			return status;
	}

	return status;
}