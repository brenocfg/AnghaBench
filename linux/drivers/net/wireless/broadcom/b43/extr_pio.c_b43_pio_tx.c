#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_5__ {struct b43_pio_txqueue* tx_queue_mcast; } ;
struct b43_wldev {TYPE_2__* wl; TYPE_1__ pio; } ;
struct b43_pio_txqueue {unsigned int buffer_size; scalar_t__ free_packet_slots; unsigned int buffer_used; int stopped; int /*<<< orphan*/  queue_prio; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int EBUSY ; 
 int ENOBUFS ; 
 int ENOKEY ; 
 int /*<<< orphan*/  IEEE80211_FCTL_MOREDATA ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_SEND_AFTER_DTIM ; 
 unsigned int b43_txhdr_size (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  b43err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  b43warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pio_tx_frame (struct b43_pio_txqueue*,struct sk_buff*) ; 
 unsigned int roundup (int,int) ; 
 struct b43_pio_txqueue* select_queue_by_priority (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int b43_pio_tx(struct b43_wldev *dev, struct sk_buff *skb)
{
	struct b43_pio_txqueue *q;
	struct ieee80211_hdr *hdr;
	unsigned int hdrlen, total_len;
	int err = 0;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	hdr = (struct ieee80211_hdr *)skb->data;

	if (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) {
		/* The multicast queue will be sent after the DTIM. */
		q = dev->pio.tx_queue_mcast;
		/* Set the frame More-Data bit. Ucode will clear it
		 * for us on the last frame. */
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	} else {
		/* Decide by priority where to put this frame. */
		q = select_queue_by_priority(dev, skb_get_queue_mapping(skb));
	}

	hdrlen = b43_txhdr_size(dev);
	total_len = roundup(skb->len + hdrlen, 4);

	if (unlikely(total_len > q->buffer_size)) {
		err = -ENOBUFS;
		b43dbg(dev->wl, "PIO: TX packet longer than queue.\n");
		goto out;
	}
	if (unlikely(q->free_packet_slots == 0)) {
		err = -ENOBUFS;
		b43warn(dev->wl, "PIO: TX packet overflow.\n");
		goto out;
	}
	B43_WARN_ON(q->buffer_used > q->buffer_size);

	if (total_len > (q->buffer_size - q->buffer_used)) {
		/* Not enough memory on the queue. */
		err = -EBUSY;
		ieee80211_stop_queue(dev->wl->hw, skb_get_queue_mapping(skb));
		q->stopped = true;
		goto out;
	}

	/* Assign the queue number to the ring (if not already done before)
	 * so TX status handling can use it. The mac80211-queue to b43-queue
	 * mapping is static, so we don't need to store it per frame. */
	q->queue_prio = skb_get_queue_mapping(skb);

	err = pio_tx_frame(q, skb);
	if (unlikely(err == -ENOKEY)) {
		/* Drop this packet, as we don't have the encryption key
		 * anymore and must not transmit it unencrypted. */
		ieee80211_free_txskb(dev->wl->hw, skb);
		err = 0;
		goto out;
	}
	if (unlikely(err)) {
		b43err(dev->wl, "PIO transmission failure\n");
		goto out;
	}

	B43_WARN_ON(q->buffer_used > q->buffer_size);
	if (((q->buffer_size - q->buffer_used) < roundup(2 + 2 + 6, 4)) ||
	    (q->free_packet_slots == 0)) {
		/* The queue is full. */
		ieee80211_stop_queue(dev->wl->hw, skb_get_queue_mapping(skb));
		q->stopped = true;
	}

out:
	return err;
}