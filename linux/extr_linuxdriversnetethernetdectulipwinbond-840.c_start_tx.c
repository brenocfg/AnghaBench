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
struct netdev_private {int cur_tx; scalar_t__ tx_q_bytes; scalar_t__ dirty_tx; int drv_flags; int tx_full; int /*<<< orphan*/  lock; scalar_t__ base_addr; TYPE_1__* tx_ring; scalar_t__* tx_addr; struct sk_buff** tx_skbuff; int /*<<< orphan*/  pci_dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int length; int /*<<< orphan*/  status; scalar_t__ buffer2; scalar_t__ buffer1; } ;

/* Variables and functions */
 int DescEndRing ; 
 int /*<<< orphan*/  DescOwned ; 
 int DescWholePkt ; 
 int HasBrokenTx ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_BUFLIMIT ; 
 scalar_t__ TX_BUG_FIFO_LIMIT ; 
 scalar_t__ TX_QUEUE_LEN ; 
 int TX_RING_SIZE ; 
 scalar_t__ TxStartDemand ; 
 int debug ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,scalar_t__,unsigned int) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t start_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	unsigned entry;

	/* Caution: the write order is important here, set the field
	   with the "ownership" bits last. */

	/* Calculate the next Tx descriptor entry. */
	entry = np->cur_tx % TX_RING_SIZE;

	np->tx_addr[entry] = pci_map_single(np->pci_dev,
				skb->data,skb->len, PCI_DMA_TODEVICE);
	np->tx_skbuff[entry] = skb;

	np->tx_ring[entry].buffer1 = np->tx_addr[entry];
	if (skb->len < TX_BUFLIMIT) {
		np->tx_ring[entry].length = DescWholePkt | skb->len;
	} else {
		int len = skb->len - TX_BUFLIMIT;

		np->tx_ring[entry].buffer2 = np->tx_addr[entry]+TX_BUFLIMIT;
		np->tx_ring[entry].length = DescWholePkt | (len << 11) | TX_BUFLIMIT;
	}
	if(entry == TX_RING_SIZE-1)
		np->tx_ring[entry].length |= DescEndRing;

	/* Now acquire the irq spinlock.
	 * The difficult race is the ordering between
	 * increasing np->cur_tx and setting DescOwned:
	 * - if np->cur_tx is increased first the interrupt
	 *   handler could consider the packet as transmitted
	 *   since DescOwned is cleared.
	 * - If DescOwned is set first the NIC could report the
	 *   packet as sent, but the interrupt handler would ignore it
	 *   since the np->cur_tx was not yet increased.
	 */
	spin_lock_irq(&np->lock);
	np->cur_tx++;

	wmb(); /* flush length, buffer1, buffer2 */
	np->tx_ring[entry].status = DescOwned;
	wmb(); /* flush status and kick the hardware */
	iowrite32(0, np->base_addr + TxStartDemand);
	np->tx_q_bytes += skb->len;
	/* Work around horrible bug in the chip by marking the queue as full
	   when we do not have FIFO room for a maximum sized packet. */
	if (np->cur_tx - np->dirty_tx > TX_QUEUE_LEN ||
		((np->drv_flags & HasBrokenTx) && np->tx_q_bytes > TX_BUG_FIFO_LIMIT)) {
		netif_stop_queue(dev);
		wmb();
		np->tx_full = 1;
	}
	spin_unlock_irq(&np->lock);

	if (debug > 4) {
		netdev_dbg(dev, "Transmit frame #%d queued in slot %d\n",
			   np->cur_tx, entry);
	}
	return NETDEV_TX_OK;
}