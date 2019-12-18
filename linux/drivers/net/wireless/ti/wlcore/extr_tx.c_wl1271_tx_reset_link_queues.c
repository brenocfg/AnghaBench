#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct wl1271_link {TYPE_3__* wlvif; int /*<<< orphan*/ * tx_queue; } ;
struct wl1271 {int* tx_queue_count; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  hw; struct wl1271_link* links; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ status; } ;
struct TYPE_6__ {int* tx_queue_count; } ;
struct TYPE_4__ {int idx; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int NUM_TX_QUEUES ; 
 int /*<<< orphan*/  ieee80211_tx_status_ni (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,struct sk_buff*) ; 
 int /*<<< orphan*/  wl1271_handle_tx_low_watermark (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_is_dummy_packet (struct wl1271*,struct sk_buff*) ; 

void wl1271_tx_reset_link_queues(struct wl1271 *wl, u8 hlid)
{
	struct sk_buff *skb;
	int i;
	unsigned long flags;
	struct ieee80211_tx_info *info;
	int total[NUM_TX_QUEUES];
	struct wl1271_link *lnk = &wl->links[hlid];

	for (i = 0; i < NUM_TX_QUEUES; i++) {
		total[i] = 0;
		while ((skb = skb_dequeue(&lnk->tx_queue[i]))) {
			wl1271_debug(DEBUG_TX, "link freeing skb 0x%p", skb);

			if (!wl12xx_is_dummy_packet(wl, skb)) {
				info = IEEE80211_SKB_CB(skb);
				info->status.rates[0].idx = -1;
				info->status.rates[0].count = 0;
				ieee80211_tx_status_ni(wl->hw, skb);
			}

			total[i]++;
		}
	}

	spin_lock_irqsave(&wl->wl_lock, flags);
	for (i = 0; i < NUM_TX_QUEUES; i++) {
		wl->tx_queue_count[i] -= total[i];
		if (lnk->wlvif)
			lnk->wlvif->tx_queue_count[i] -= total[i];
	}
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	wl1271_handle_tx_low_watermark(wl);
}