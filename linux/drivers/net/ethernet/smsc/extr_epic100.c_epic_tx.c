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
struct sk_buff {scalar_t__ len; } ;
struct TYPE_3__ {int collisions; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct epic_private {unsigned int cur_tx; unsigned int dirty_tx; int /*<<< orphan*/  tx_full; struct sk_buff** tx_skbuff; TYPE_2__* tx_ring; int /*<<< orphan*/  pci_dev; } ;
struct TYPE_4__ {int txstatus; int /*<<< orphan*/  bufaddr; } ;

/* Variables and functions */
 int DescOwn ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_QUEUE_LEN ; 
 unsigned int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  epic_tx_error (struct net_device*,struct epic_private*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void epic_tx(struct net_device *dev, struct epic_private *ep)
{
	unsigned int dirty_tx, cur_tx;

	/*
	 * Note: if this lock becomes a problem we can narrow the locked
	 * region at the cost of occasionally grabbing the lock more times.
	 */
	cur_tx = ep->cur_tx;
	for (dirty_tx = ep->dirty_tx; cur_tx - dirty_tx > 0; dirty_tx++) {
		struct sk_buff *skb;
		int entry = dirty_tx % TX_RING_SIZE;
		int txstatus = ep->tx_ring[entry].txstatus;

		if (txstatus & DescOwn)
			break;	/* It still hasn't been Txed */

		if (likely(txstatus & 0x0001)) {
			dev->stats.collisions += (txstatus >> 8) & 15;
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += ep->tx_skbuff[entry]->len;
		} else
			epic_tx_error(dev, ep, txstatus);

		/* Free the original skb. */
		skb = ep->tx_skbuff[entry];
		pci_unmap_single(ep->pci_dev, ep->tx_ring[entry].bufaddr,
				 skb->len, PCI_DMA_TODEVICE);
		dev_consume_skb_irq(skb);
		ep->tx_skbuff[entry] = NULL;
	}

#ifndef final_version
	if (cur_tx - dirty_tx > TX_RING_SIZE) {
		netdev_warn(dev, "Out-of-sync dirty pointer, %d vs. %d, full=%d.\n",
			    dirty_tx, cur_tx, ep->tx_full);
		dirty_tx += TX_RING_SIZE;
	}
#endif
	ep->dirty_tx = dirty_tx;
	if (ep->tx_full && cur_tx - dirty_tx < TX_QUEUE_LEN - 4) {
		/* The ring is no longer full, allow new TX entries. */
		ep->tx_full = 0;
		netif_wake_queue(dev);
	}
}