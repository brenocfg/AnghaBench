#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wl1271_tx_hw_descr {int dummy; } ;
struct wl1271 {int num_links; int num_tx_desc; int quirks; int /*<<< orphan*/  hw; struct sk_buff** tx_frames; scalar_t__* tx_queue_count; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_8__ {TYPE_3__* rates; } ;
struct TYPE_6__ {TYPE_1__* hw_key; } ;
struct ieee80211_tx_info {TYPE_4__ status; TYPE_2__ control; } ;
struct TYPE_7__ {int idx; scalar_t__ count; } ;
struct TYPE_5__ {scalar_t__ cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int NUM_TX_QUEUES ; 
 int WL1271_EXTRA_SPACE_TKIP ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 int WLCORE_QUIRK_TKIP_HEADER_SPACE ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_ni (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,struct sk_buff*) ; 
 int /*<<< orphan*/  wl1271_free_tx_id (struct wl1271*,int) ; 
 int /*<<< orphan*/  wl1271_handle_tx_low_watermark (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_tx_reset_link_queues (struct wl1271*,int) ; 
 scalar_t__ wl1271_tx_total_queue_count (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_is_dummy_packet (struct wl1271*,struct sk_buff*) ; 

void wl12xx_tx_reset(struct wl1271 *wl)
{
	int i;
	struct sk_buff *skb;
	struct ieee80211_tx_info *info;

	/* only reset the queues if something bad happened */
	if (wl1271_tx_total_queue_count(wl) != 0) {
		for (i = 0; i < wl->num_links; i++)
			wl1271_tx_reset_link_queues(wl, i);

		for (i = 0; i < NUM_TX_QUEUES; i++)
			wl->tx_queue_count[i] = 0;
	}

	/*
	 * Make sure the driver is at a consistent state, in case this
	 * function is called from a context other than interface removal.
	 * This call will always wake the TX queues.
	 */
	wl1271_handle_tx_low_watermark(wl);

	for (i = 0; i < wl->num_tx_desc; i++) {
		if (wl->tx_frames[i] == NULL)
			continue;

		skb = wl->tx_frames[i];
		wl1271_free_tx_id(wl, i);
		wl1271_debug(DEBUG_TX, "freeing skb 0x%p", skb);

		if (!wl12xx_is_dummy_packet(wl, skb)) {
			/*
			 * Remove private headers before passing the skb to
			 * mac80211
			 */
			info = IEEE80211_SKB_CB(skb);
			skb_pull(skb, sizeof(struct wl1271_tx_hw_descr));
			if ((wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE) &&
			    info->control.hw_key &&
			    info->control.hw_key->cipher ==
			    WLAN_CIPHER_SUITE_TKIP) {
				int hdrlen = ieee80211_get_hdrlen_from_skb(skb);
				memmove(skb->data + WL1271_EXTRA_SPACE_TKIP,
					skb->data, hdrlen);
				skb_pull(skb, WL1271_EXTRA_SPACE_TKIP);
			}

			info->status.rates[0].idx = -1;
			info->status.rates[0].count = 0;

			ieee80211_tx_status_ni(wl->hw, skb);
		}
	}
}