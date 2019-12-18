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
struct TYPE_6__ {scalar_t__ qlen; } ;
struct TYPE_5__ {int qlen; } ;
struct TYPE_8__ {scalar_t__ qlen; } ;
struct usbnet {int /*<<< orphan*/  net; TYPE_2__ txq; int /*<<< orphan*/  bh; TYPE_1__ rxq; int /*<<< orphan*/  flags; int /*<<< orphan*/  delay; int /*<<< orphan*/  wait; TYPE_4__ done; } ;
struct timer_list {int dummy; } ;
struct skb_data {int state; TYPE_3__* urb; } ;
struct sk_buff {scalar_t__ cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOLINK ; 
 int /*<<< orphan*/  EVENT_RX_HALT ; 
 int /*<<< orphan*/  EVENT_RX_KILL ; 
 int /*<<< orphan*/  EVENT_RX_PAUSED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int RX_QLEN (struct usbnet*) ; 
 scalar_t__ TX_QLEN (struct usbnet*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delay ; 
 struct usbnet* dev ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct usbnet* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ netif_device_present (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_alloc_submit (struct usbnet*,int /*<<< orphan*/ ) ; 
#define  rx_cleanup 130 
#define  rx_done 129 
 int /*<<< orphan*/  rx_process (struct usbnet*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (TYPE_4__*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
#define  tx_done 128 
 int /*<<< orphan*/  usb_free_urb (TYPE_3__*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbnet_bh (struct timer_list *t)
{
	struct usbnet		*dev = from_timer(dev, t, delay);
	struct sk_buff		*skb;
	struct skb_data		*entry;

	while ((skb = skb_dequeue (&dev->done))) {
		entry = (struct skb_data *) skb->cb;
		switch (entry->state) {
		case rx_done:
			entry->state = rx_cleanup;
			rx_process (dev, skb);
			continue;
		case tx_done:
			kfree(entry->urb->sg);
			/* fall through */
		case rx_cleanup:
			usb_free_urb (entry->urb);
			dev_kfree_skb (skb);
			continue;
		default:
			netdev_dbg(dev->net, "bogus skb state %d\n", entry->state);
		}
	}

	/* restart RX again after disabling due to high error rate */
	clear_bit(EVENT_RX_KILL, &dev->flags);

	/* waiting for all pending urbs to complete?
	 * only then can we forgo submitting anew
	 */
	if (waitqueue_active(&dev->wait)) {
		if (dev->txq.qlen + dev->rxq.qlen + dev->done.qlen == 0)
			wake_up_all(&dev->wait);

	// or are we maybe short a few urbs?
	} else if (netif_running (dev->net) &&
		   netif_device_present (dev->net) &&
		   netif_carrier_ok(dev->net) &&
		   !timer_pending(&dev->delay) &&
		   !test_bit(EVENT_RX_PAUSED, &dev->flags) &&
		   !test_bit(EVENT_RX_HALT, &dev->flags)) {
		int	temp = dev->rxq.qlen;

		if (temp < RX_QLEN(dev)) {
			if (rx_alloc_submit(dev, GFP_ATOMIC) == -ENOLINK)
				return;
			if (temp != dev->rxq.qlen)
				netif_dbg(dev, link, dev->net,
					  "rxqlen %d --> %d\n",
					  temp, dev->rxq.qlen);
			if (dev->rxq.qlen < RX_QLEN(dev))
				tasklet_schedule (&dev->bh);
		}
		if (dev->txq.qlen < TX_QLEN (dev))
			netif_wake_queue (dev->net);
	}
}