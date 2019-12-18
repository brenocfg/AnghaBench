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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int tx_bytes; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct el3_private {int /*<<< orphan*/  window_lock; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int SetTxThreshold ; 
 scalar_t__ TX_FIFO ; 
 scalar_t__ TxFree ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int inw (scalar_t__) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outsl (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pop_tx_status (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t el3_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
	unsigned int ioaddr = dev->base_addr;
	struct el3_private *lp = netdev_priv(dev);
	unsigned long flags;

	pr_debug("%s: el3_start_xmit(length = %ld) called, "
		  "status %4.4x.\n", dev->name, (long)skb->len,
		  inw(ioaddr + EL3_STATUS));

	spin_lock_irqsave(&lp->window_lock, flags);

	dev->stats.tx_bytes += skb->len;

	/* Put out the doubleword header... */
	outw(skb->len, ioaddr + TX_FIFO);
	outw(0, ioaddr + TX_FIFO);
	/* ... and the packet rounded to a doubleword. */
	outsl(ioaddr + TX_FIFO, skb->data, (skb->len+3)>>2);

	/* TxFree appears only in Window 1, not offset 0x1c. */
	if (inw(ioaddr + TxFree) <= 1536) {
		netif_stop_queue(dev);
		/* Interrupt us when the FIFO has room for max-sized packet. 
		   The threshold is in units of dwords. */
		outw(SetTxThreshold + (1536>>2), ioaddr + EL3_CMD);
	}

	pop_tx_status(dev);
	spin_unlock_irqrestore(&lp->window_lock, flags);
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}