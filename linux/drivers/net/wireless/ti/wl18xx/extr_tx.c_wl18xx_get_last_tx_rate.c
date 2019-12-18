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
typedef  size_t u8 ;
struct wl12xx_vif {scalar_t__ channel_type; } ;
struct wl1271 {TYPE_1__* links; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_rate {size_t idx; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {size_t fw_rate_idx; } ;

/* Variables and functions */
 size_t CONF_HW_RATE_INDEX_54MBPS ; 
 size_t CONF_HW_RATE_INDEX_6MBPS ; 
 size_t CONF_HW_RATE_INDEX_MAX ; 
 size_t CONF_HW_RATE_INDEX_MCS0 ; 
 size_t CONF_HW_RATE_INDEX_MCS15_SGI ; 
 size_t CONF_HW_RATE_INDEX_MCS7_SGI ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_SHORT_GI ; 
 size_t NL80211_BAND_5GHZ ; 
 scalar_t__ NL80211_CHAN_HT40MINUS ; 
 scalar_t__ NL80211_CHAN_HT40PLUS ; 
 int /*<<< orphan*/  wl1271_error (char*,size_t) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 

__attribute__((used)) static
void wl18xx_get_last_tx_rate(struct wl1271 *wl, struct ieee80211_vif *vif,
			     u8 band, struct ieee80211_tx_rate *rate, u8 hlid)
{
	u8 fw_rate = wl->links[hlid].fw_rate_idx;

	if (fw_rate > CONF_HW_RATE_INDEX_MAX) {
		wl1271_error("last Tx rate invalid: %d", fw_rate);
		rate->idx = 0;
		rate->flags = 0;
		return;
	}

	if (fw_rate <= CONF_HW_RATE_INDEX_54MBPS) {
		rate->idx = fw_rate;
		if (band == NL80211_BAND_5GHZ)
			rate->idx -= CONF_HW_RATE_INDEX_6MBPS;
		rate->flags = 0;
	} else {
		rate->flags = IEEE80211_TX_RC_MCS;
		rate->idx = fw_rate - CONF_HW_RATE_INDEX_MCS0;

		/* SGI modifier is counted as a separate rate */
		if (fw_rate >= CONF_HW_RATE_INDEX_MCS7_SGI)
			(rate->idx)--;
		if (fw_rate == CONF_HW_RATE_INDEX_MCS15_SGI)
			(rate->idx)--;

		/* this also covers the 40Mhz SGI case (= MCS15) */
		if (fw_rate == CONF_HW_RATE_INDEX_MCS7_SGI ||
		    fw_rate == CONF_HW_RATE_INDEX_MCS15_SGI)
			rate->flags |= IEEE80211_TX_RC_SHORT_GI;

		if (fw_rate > CONF_HW_RATE_INDEX_MCS7_SGI && vif) {
			struct wl12xx_vif *wlvif = wl12xx_vif_to_data(vif);
			if (wlvif->channel_type == NL80211_CHAN_HT40MINUS ||
			    wlvif->channel_type == NL80211_CHAN_HT40PLUS) {
				/* adjustment needed for range 0-7 */
				rate->idx -= 8;
				rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
			}
		}
	}
}