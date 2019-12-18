#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_tx_info {int dummy; } ;
struct b43_wldev {TYPE_1__* wl; } ;
struct b43_txstatus {int /*<<< orphan*/  cookie; } ;
struct b43_pio_txqueue {unsigned int buffer_used; int free_packet_slots; int stopped; int /*<<< orphan*/  queue_prio; int /*<<< orphan*/  packets_list; } ;
struct b43_pio_txpacket {int /*<<< orphan*/  list; TYPE_2__* skb; } ;
struct TYPE_5__ {unsigned int len; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (TYPE_2__*) ; 
 int /*<<< orphan*/  b43_fill_txstatus_report (struct b43_wldev*,struct ieee80211_tx_info*,struct b43_txstatus const*) ; 
 unsigned int b43_txhdr_size (struct b43_wldev*) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct b43_pio_txqueue* parse_cookie (struct b43_wldev*,int /*<<< orphan*/ ,struct b43_pio_txpacket**) ; 
 unsigned int roundup (unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

void b43_pio_handle_txstatus(struct b43_wldev *dev,
			     const struct b43_txstatus *status)
{
	struct b43_pio_txqueue *q;
	struct b43_pio_txpacket *pack = NULL;
	unsigned int total_len;
	struct ieee80211_tx_info *info;

	q = parse_cookie(dev, status->cookie, &pack);
	if (unlikely(!q))
		return;
	B43_WARN_ON(!pack);

	info = IEEE80211_SKB_CB(pack->skb);

	b43_fill_txstatus_report(dev, info, status);

	total_len = pack->skb->len + b43_txhdr_size(dev);
	total_len = roundup(total_len, 4);
	q->buffer_used -= total_len;
	q->free_packet_slots += 1;

	ieee80211_tx_status(dev->wl->hw, pack->skb);
	pack->skb = NULL;
	list_add(&pack->list, &q->packets_list);

	if (q->stopped) {
		ieee80211_wake_queue(dev->wl->hw, q->queue_prio);
		q->stopped = false;
	}
}