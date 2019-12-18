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
typedef  int u_long ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct net_device {int base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ lock; int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int tx_bytes; } ;
struct de4x5_private {size_t tx_new; int txRingSize; TYPE_2__ cache; int /*<<< orphan*/  lock; TYPE_1__ stats; scalar_t__* tx_skb; scalar_t__ interrupt; int /*<<< orphan*/  tx_enable; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DE4X5_IMR ; 
 int /*<<< orphan*/  DE4X5_OMR ; 
 int /*<<< orphan*/  DE4X5_STS ; 
 int /*<<< orphan*/  DE4X5_TPD ; 
 int DEBUG_TX ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  POLL_DEMAND ; 
 int TD_FS ; 
 int TD_IC ; 
 int TD_LS ; 
 scalar_t__ TX_BUFFS_AVAIL ; 
 int de4x5_debug ; 
 struct sk_buff* de4x5_get_cache (struct net_device*) ; 
 int /*<<< orphan*/  de4x5_put_cache (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  de4x5_putb_cache (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  de4x5_tx (struct net_device*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_packet (struct net_device*,int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 struct de4x5_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static netdev_tx_t
de4x5_queue_pkt(struct sk_buff *skb, struct net_device *dev)
{
    struct de4x5_private *lp = netdev_priv(dev);
    u_long iobase = dev->base_addr;
    u_long flags = 0;

    netif_stop_queue(dev);
    if (!lp->tx_enable)                   /* Cannot send for now */
		goto tx_err;

    /*
    ** Clean out the TX ring asynchronously to interrupts - sometimes the
    ** interrupts are lost by delayed descriptor status updates relative to
    ** the irq assertion, especially with a busy PCI bus.
    */
    spin_lock_irqsave(&lp->lock, flags);
    de4x5_tx(dev);
    spin_unlock_irqrestore(&lp->lock, flags);

    /* Test if cache is already locked - requeue skb if so */
    if (test_and_set_bit(0, (void *)&lp->cache.lock) && !lp->interrupt)
		goto tx_err;

    /* Transmit descriptor ring full or stale skb */
    if (netif_queue_stopped(dev) || (u_long) lp->tx_skb[lp->tx_new] > 1) {
	if (lp->interrupt) {
	    de4x5_putb_cache(dev, skb);          /* Requeue the buffer */
	} else {
	    de4x5_put_cache(dev, skb);
	}
	if (de4x5_debug & DEBUG_TX) {
	    printk("%s: transmit busy, lost media or stale skb found:\n  STS:%08x\n  tbusy:%d\n  IMR:%08x\n  OMR:%08x\n Stale skb: %s\n",dev->name, inl(DE4X5_STS), netif_queue_stopped(dev), inl(DE4X5_IMR), inl(DE4X5_OMR), ((u_long) lp->tx_skb[lp->tx_new] > 1) ? "YES" : "NO");
	}
    } else if (skb->len > 0) {
	/* If we already have stuff queued locally, use that first */
	if (!skb_queue_empty(&lp->cache.queue) && !lp->interrupt) {
	    de4x5_put_cache(dev, skb);
	    skb = de4x5_get_cache(dev);
	}

	while (skb && !netif_queue_stopped(dev) &&
	       (u_long) lp->tx_skb[lp->tx_new] <= 1) {
	    spin_lock_irqsave(&lp->lock, flags);
	    netif_stop_queue(dev);
	    load_packet(dev, skb->data, TD_IC | TD_LS | TD_FS | skb->len, skb);
 	    lp->stats.tx_bytes += skb->len;
	    outl(POLL_DEMAND, DE4X5_TPD);/* Start the TX */

	    lp->tx_new = (lp->tx_new + 1) % lp->txRingSize;

	    if (TX_BUFFS_AVAIL) {
		netif_start_queue(dev);         /* Another pkt may be queued */
	    }
	    skb = de4x5_get_cache(dev);
	    spin_unlock_irqrestore(&lp->lock, flags);
	}
	if (skb) de4x5_putb_cache(dev, skb);
    }

    lp->cache.lock = 0;

    return NETDEV_TX_OK;
tx_err:
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}