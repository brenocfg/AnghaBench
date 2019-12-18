#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wl1271_tx_hw_descr {int /*<<< orphan*/  hlid; } ;
struct TYPE_7__ {int /*<<< orphan*/  retry_count; } ;
struct wl1271 {int num_tx_desc; int quirks; int /*<<< orphan*/  netstack_work; int /*<<< orphan*/  freezable_wq; int /*<<< orphan*/  deferred_tx_queue; TYPE_2__ stats; struct sk_buff** tx_frames; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_9__ {TYPE_3__* hw_key; int /*<<< orphan*/  vif; } ;
struct TYPE_6__ {int ack_signal; TYPE_5__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_4__ control; TYPE_1__ status; int /*<<< orphan*/  band; } ;
struct TYPE_10__ {int count; } ;
struct TYPE_8__ {scalar_t__ cipher; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_TX ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_STAT_ACK ; 
 int WL1271_EXTRA_SPACE_TKIP ; 
 int WL18XX_TX_STATUS_DESC_ID_MASK ; 
 int /*<<< orphan*/  WL18XX_TX_STATUS_STAT_BIT_IDX ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 int WLCORE_QUIRK_TKIP_HEADER_SPACE ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int,struct sk_buff*,int) ; 
 int /*<<< orphan*/  wl1271_free_tx_id (struct wl1271*,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 
 scalar_t__ wl12xx_is_dummy_packet (struct wl1271*,struct sk_buff*) ; 
 int /*<<< orphan*/  wl18xx_get_last_tx_rate (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl18xx_tx_complete_packet(struct wl1271 *wl, u8 tx_stat_byte)
{
	struct ieee80211_tx_info *info;
	struct sk_buff *skb;
	int id = tx_stat_byte & WL18XX_TX_STATUS_DESC_ID_MASK;
	bool tx_success;
	struct wl1271_tx_hw_descr *tx_desc;

	/* check for id legality */
	if (unlikely(id >= wl->num_tx_desc || wl->tx_frames[id] == NULL)) {
		wl1271_warning("illegal id in tx completion: %d", id);
		return;
	}

	/* a zero bit indicates Tx success */
	tx_success = !(tx_stat_byte & BIT(WL18XX_TX_STATUS_STAT_BIT_IDX));

	skb = wl->tx_frames[id];
	info = IEEE80211_SKB_CB(skb);
	tx_desc = (struct wl1271_tx_hw_descr *)skb->data;

	if (wl12xx_is_dummy_packet(wl, skb)) {
		wl1271_free_tx_id(wl, id);
		return;
	}

	/* update the TX status info */
	if (tx_success && !(info->flags & IEEE80211_TX_CTL_NO_ACK))
		info->flags |= IEEE80211_TX_STAT_ACK;
	/*
	 * first pass info->control.vif while it's valid, and then fill out
	 * the info->status structures
	 */
	wl18xx_get_last_tx_rate(wl, info->control.vif,
				info->band,
				&info->status.rates[0],
				tx_desc->hlid);

	info->status.rates[0].count = 1; /* no data about retries */
	info->status.ack_signal = -1;

	if (!tx_success)
		wl->stats.retry_count++;

	/*
	 * TODO: update sequence number for encryption? seems to be
	 * unsupported for now. needed for recovery with encryption.
	 */

	/* remove private header from packet */
	skb_pull(skb, sizeof(struct wl1271_tx_hw_descr));

	/* remove TKIP header space if present */
	if ((wl->quirks & WLCORE_QUIRK_TKIP_HEADER_SPACE) &&
	    info->control.hw_key &&
	    info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) {
		int hdrlen = ieee80211_get_hdrlen_from_skb(skb);
		memmove(skb->data + WL1271_EXTRA_SPACE_TKIP, skb->data, hdrlen);
		skb_pull(skb, WL1271_EXTRA_SPACE_TKIP);
	}

	wl1271_debug(DEBUG_TX, "tx status id %u skb 0x%p success %d",
		     id, skb, tx_success);

	/* return the packet to the stack */
	skb_queue_tail(&wl->deferred_tx_queue, skb);
	queue_work(wl->freezable_wq, &wl->netstack_work);
	wl1271_free_tx_id(wl, id);
}