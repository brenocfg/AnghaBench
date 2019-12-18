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
struct skb_data {int state; int /*<<< orphan*/  urb; } ;
struct sk_buff {scalar_t__ cb; } ;
struct lan78xx_net {int delta; int /*<<< orphan*/  flags; int /*<<< orphan*/  delay; int /*<<< orphan*/  txq_pend; int /*<<< orphan*/  stat_monitor; int /*<<< orphan*/  net; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_RX_HALT ; 
 scalar_t__ STAT_UPDATE_TIMER ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lan78xx_rx_bh (struct lan78xx_net*) ; 
 int /*<<< orphan*/  lan78xx_tx_bh (struct lan78xx_net*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ netif_device_present (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
#define  rx_cleanup 130 
#define  rx_done 129 
 int /*<<< orphan*/  rx_process (struct lan78xx_net*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
#define  tx_done 128 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan78xx_bh(unsigned long param)
{
	struct lan78xx_net *dev = (struct lan78xx_net *)param;
	struct sk_buff *skb;
	struct skb_data *entry;

	while ((skb = skb_dequeue(&dev->done))) {
		entry = (struct skb_data *)(skb->cb);
		switch (entry->state) {
		case rx_done:
			entry->state = rx_cleanup;
			rx_process(dev, skb);
			continue;
		case tx_done:
			usb_free_urb(entry->urb);
			dev_kfree_skb(skb);
			continue;
		case rx_cleanup:
			usb_free_urb(entry->urb);
			dev_kfree_skb(skb);
			continue;
		default:
			netdev_dbg(dev->net, "skb state %d\n", entry->state);
			return;
		}
	}

	if (netif_device_present(dev->net) && netif_running(dev->net)) {
		/* reset update timer delta */
		if (timer_pending(&dev->stat_monitor) && (dev->delta != 1)) {
			dev->delta = 1;
			mod_timer(&dev->stat_monitor,
				  jiffies + STAT_UPDATE_TIMER);
		}

		if (!skb_queue_empty(&dev->txq_pend))
			lan78xx_tx_bh(dev);

		if (!timer_pending(&dev->delay) &&
		    !test_bit(EVENT_RX_HALT, &dev->flags))
			lan78xx_rx_bh(dev);
	}
}