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
typedef  int /*<<< orphan*/  u32 ;
struct wl12xx_vif {scalar_t__ channel_type; int /*<<< orphan*/  rate_set; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_TX_MIMO_RATES ; 
 int /*<<< orphan*/  CONF_TX_RATE_USE_WIDE_CHAN ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 scalar_t__ NL80211_CHAN_HT40MINUS ; 
 scalar_t__ NL80211_CHAN_HT40PLUS ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wl18xx_is_mimo_supported (struct wl1271*) ; 

__attribute__((used)) static u32 wl18xx_sta_get_ap_rate_mask(struct wl1271 *wl,
				       struct wl12xx_vif *wlvif)
{
	u32 hw_rate_set = wlvif->rate_set;

	if (wlvif->channel_type == NL80211_CHAN_HT40MINUS ||
	    wlvif->channel_type == NL80211_CHAN_HT40PLUS) {
		wl1271_debug(DEBUG_ACX, "using wide channel rate mask");
		hw_rate_set |= CONF_TX_RATE_USE_WIDE_CHAN;

		/* we don't support MIMO in wide-channel mode */
		hw_rate_set &= ~CONF_TX_MIMO_RATES;
	} else if (wl18xx_is_mimo_supported(wl)) {
		wl1271_debug(DEBUG_ACX, "using MIMO channel rate mask");
		hw_rate_set |= CONF_TX_MIMO_RATES;
	}

	return hw_rate_set;
}