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
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_aborted_errors; } ;
struct net_device {int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct el3_private {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int SetTxThreshold ; 
 scalar_t__ TX_FIFO ; 
 scalar_t__ TX_FREE ; 
 scalar_t__ TX_STATUS ; 
 int TxEnable ; 
 int TxReset ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int el3_debug ; 
 short inb (scalar_t__) ; 
 int inw (scalar_t__) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outsl (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t
el3_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct el3_private *lp = netdev_priv(dev);
	int ioaddr = dev->base_addr;
	unsigned long flags;

	netif_stop_queue (dev);

	dev->stats.tx_bytes += skb->len;

	if (el3_debug > 4) {
		pr_debug("%s: el3_start_xmit(length = %u) called, status %4.4x.\n",
			   dev->name, skb->len, inw(ioaddr + EL3_STATUS));
	}
	/*
	 *	We lock the driver against other processors. Note
	 *	we don't need to lock versus the IRQ as we suspended
	 *	that. This means that we lose the ability to take
	 *	an RX during a TX upload. That sucks a bit with SMP
	 *	on an original 3c509 (2K buffer)
	 *
	 *	Using disable_irq stops us crapping on other
	 *	time sensitive devices.
	 */

	spin_lock_irqsave(&lp->lock, flags);

	/* Put out the doubleword header... */
	outw(skb->len, ioaddr + TX_FIFO);
	outw(0x00, ioaddr + TX_FIFO);
	/* ... and the packet rounded to a doubleword. */
	outsl(ioaddr + TX_FIFO, skb->data, (skb->len + 3) >> 2);

	if (inw(ioaddr + TX_FREE) > 1536)
		netif_start_queue(dev);
	else
		/* Interrupt us when the FIFO has room for max-sized packet. */
		outw(SetTxThreshold + 1536, ioaddr + EL3_CMD);

	spin_unlock_irqrestore(&lp->lock, flags);

	dev_consume_skb_any (skb);

	/* Clear the Tx status stack. */
	{
		short tx_status;
		int i = 4;

		while (--i > 0	&&	(tx_status = inb(ioaddr + TX_STATUS)) > 0) {
			if (tx_status & 0x38) dev->stats.tx_aborted_errors++;
			if (tx_status & 0x30) outw(TxReset, ioaddr + EL3_CMD);
			if (tx_status & 0x3C) outw(TxEnable, ioaddr + EL3_CMD);
			outb(0x00, ioaddr + TX_STATUS); /* Pop the status stack. */
		}
	}
	return NETDEV_TX_OK;
}