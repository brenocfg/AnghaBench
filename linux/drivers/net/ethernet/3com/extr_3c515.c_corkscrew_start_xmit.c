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
struct sk_buff {int len; struct boom_tx_desc* data; } ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_fifo_errors; } ;
struct net_device {int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct corkscrew_private {int cur_tx; int tx_full; int dirty_tx; struct sk_buff* tx_skb; scalar_t__ bus_master; int /*<<< orphan*/  lock; struct boom_tx_desc* tx_ring; struct sk_buff** tx_skbuff; scalar_t__ full_bus_master_tx; } ;
struct boom_tx_desc {int next; int addr; int length; int status; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int CmdInProgress ; 
 scalar_t__ DownListPtr ; 
 int DownStall ; 
 int DownUnstall ; 
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int SetTxThreshold ; 
 int StartDMADown ; 
 scalar_t__ TX_FIFO ; 
 int TX_RING_SIZE ; 
 int TxEnable ; 
 scalar_t__ TxFree ; 
 int TxReset ; 
 scalar_t__ TxStatus ; 
 scalar_t__ Wn7_MasterAddr ; 
 scalar_t__ Wn7_MasterLen ; 
 int corkscrew_debug ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 short inb (scalar_t__) ; 
 scalar_t__ inl (scalar_t__) ; 
 int inw (scalar_t__) ; 
 int isa_virt_to_bus (struct boom_tx_desc*) ; 
 struct corkscrew_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  outsl (scalar_t__,struct boom_tx_desc*,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  queued_packet ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t corkscrew_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
	struct corkscrew_private *vp = netdev_priv(dev);
	int ioaddr = dev->base_addr;

	/* Block a timer-based transmit from overlapping. */

	netif_stop_queue(dev);

	if (vp->full_bus_master_tx) {	/* BOOMERANG bus-master */
		/* Calculate the next Tx descriptor entry. */
		int entry = vp->cur_tx % TX_RING_SIZE;
		struct boom_tx_desc *prev_entry;
		unsigned long flags;
		int i;

		if (vp->tx_full)	/* No room to transmit with */
			return NETDEV_TX_BUSY;
		if (vp->cur_tx != 0)
			prev_entry = &vp->tx_ring[(vp->cur_tx - 1) % TX_RING_SIZE];
		else
			prev_entry = NULL;
		if (corkscrew_debug > 3)
			pr_debug("%s: Trying to send a packet, Tx index %d.\n",
				dev->name, vp->cur_tx);
		/* vp->tx_full = 1; */
		vp->tx_skbuff[entry] = skb;
		vp->tx_ring[entry].next = 0;
		vp->tx_ring[entry].addr = isa_virt_to_bus(skb->data);
		vp->tx_ring[entry].length = skb->len | 0x80000000;
		vp->tx_ring[entry].status = skb->len | 0x80000000;

		spin_lock_irqsave(&vp->lock, flags);
		outw(DownStall, ioaddr + EL3_CMD);
		/* Wait for the stall to complete. */
		for (i = 20; i >= 0; i--)
			if ((inw(ioaddr + EL3_STATUS) & CmdInProgress) == 0)
				break;
		if (prev_entry)
			prev_entry->next = isa_virt_to_bus(&vp->tx_ring[entry]);
		if (inl(ioaddr + DownListPtr) == 0) {
			outl(isa_virt_to_bus(&vp->tx_ring[entry]),
			     ioaddr + DownListPtr);
			queued_packet++;
		}
		outw(DownUnstall, ioaddr + EL3_CMD);
		spin_unlock_irqrestore(&vp->lock, flags);

		vp->cur_tx++;
		if (vp->cur_tx - vp->dirty_tx > TX_RING_SIZE - 1)
			vp->tx_full = 1;
		else {		/* Clear previous interrupt enable. */
			if (prev_entry)
				prev_entry->status &= ~0x80000000;
			netif_wake_queue(dev);
		}
		return NETDEV_TX_OK;
	}
	/* Put out the doubleword header... */
	outl(skb->len, ioaddr + TX_FIFO);
	dev->stats.tx_bytes += skb->len;
#ifdef VORTEX_BUS_MASTER
	if (vp->bus_master) {
		/* Set the bus-master controller to transfer the packet. */
		outl((int) (skb->data), ioaddr + Wn7_MasterAddr);
		outw((skb->len + 3) & ~3, ioaddr + Wn7_MasterLen);
		vp->tx_skb = skb;
		outw(StartDMADown, ioaddr + EL3_CMD);
		/* queue will be woken at the DMADone interrupt. */
	} else {
		/* ... and the packet rounded to a doubleword. */
		outsl(ioaddr + TX_FIFO, skb->data, (skb->len + 3) >> 2);
		dev_kfree_skb(skb);
		if (inw(ioaddr + TxFree) > 1536) {
			netif_wake_queue(dev);
		} else
			/* Interrupt us when the FIFO has room for max-sized packet. */
			outw(SetTxThreshold + (1536 >> 2),
			     ioaddr + EL3_CMD);
	}
#else
	/* ... and the packet rounded to a doubleword. */
	outsl(ioaddr + TX_FIFO, skb->data, (skb->len + 3) >> 2);
	dev_kfree_skb(skb);
	if (inw(ioaddr + TxFree) > 1536) {
		netif_wake_queue(dev);
	} else
		/* Interrupt us when the FIFO has room for max-sized packet. */
		outw(SetTxThreshold + (1536 >> 2), ioaddr + EL3_CMD);
#endif				/* bus master */


	/* Clear the Tx status stack. */
	{
		short tx_status;
		int i = 4;

		while (--i > 0 && (tx_status = inb(ioaddr + TxStatus)) > 0) {
			if (tx_status & 0x3C) {	/* A Tx-disabling error occurred.  */
				if (corkscrew_debug > 2)
					pr_debug("%s: Tx error, status %2.2x.\n",
						dev->name, tx_status);
				if (tx_status & 0x04)
					dev->stats.tx_fifo_errors++;
				if (tx_status & 0x38)
					dev->stats.tx_aborted_errors++;
				if (tx_status & 0x30) {
					int j;
					outw(TxReset, ioaddr + EL3_CMD);
					for (j = 20; j >= 0; j--)
						if (!(inw(ioaddr + EL3_STATUS) & CmdInProgress))
							break;
				}
				outw(TxEnable, ioaddr + EL3_CMD);
			}
			outb(0x00, ioaddr + TxStatus);	/* Pop the status stack. */
		}
	}
	return NETDEV_TX_OK;
}