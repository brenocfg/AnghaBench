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
struct TYPE_7__ {int collisions; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct TYPE_6__ {scalar_t__ full_duplex; } ;
struct netdev_private {scalar_t__ cur_tx; scalar_t__ dirty_tx; scalar_t__ tx_q_bytes; scalar_t__ tx_full; TYPE_4__** tx_skbuff; int /*<<< orphan*/ * tx_addr; int /*<<< orphan*/  pci_dev; TYPE_3__ stats; TYPE_2__ mii_if; TYPE_1__* tx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_8__ {scalar_t__ len; } ;
struct TYPE_5__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ TX_BUG_FIFO_LIMIT ; 
 scalar_t__ TX_QUEUE_LEN_RESTART ; 
 int TX_RING_SIZE ; 
 int debug ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (TYPE_4__*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,...) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void netdev_tx_done(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	for (; np->cur_tx - np->dirty_tx > 0; np->dirty_tx++) {
		int entry = np->dirty_tx % TX_RING_SIZE;
		int tx_status = np->tx_ring[entry].status;

		if (tx_status < 0)
			break;
		if (tx_status & 0x8000) { 	/* There was an error, log it. */
#ifndef final_version
			if (debug > 1)
				netdev_dbg(dev, "Transmit error, Tx status %08x\n",
					   tx_status);
#endif
			np->stats.tx_errors++;
			if (tx_status & 0x0104) np->stats.tx_aborted_errors++;
			if (tx_status & 0x0C80) np->stats.tx_carrier_errors++;
			if (tx_status & 0x0200) np->stats.tx_window_errors++;
			if (tx_status & 0x0002) np->stats.tx_fifo_errors++;
			if ((tx_status & 0x0080) && np->mii_if.full_duplex == 0)
				np->stats.tx_heartbeat_errors++;
		} else {
#ifndef final_version
			if (debug > 3)
				netdev_dbg(dev, "Transmit slot %d ok, Tx status %08x\n",
					   entry, tx_status);
#endif
			np->stats.tx_bytes += np->tx_skbuff[entry]->len;
			np->stats.collisions += (tx_status >> 3) & 15;
			np->stats.tx_packets++;
		}
		/* Free the original skb. */
		pci_unmap_single(np->pci_dev,np->tx_addr[entry],
					np->tx_skbuff[entry]->len,
					PCI_DMA_TODEVICE);
		np->tx_q_bytes -= np->tx_skbuff[entry]->len;
		dev_kfree_skb_irq(np->tx_skbuff[entry]);
		np->tx_skbuff[entry] = NULL;
	}
	if (np->tx_full &&
		np->cur_tx - np->dirty_tx < TX_QUEUE_LEN_RESTART &&
		np->tx_q_bytes < TX_BUG_FIFO_LIMIT) {
		/* The ring is no longer full, clear tbusy. */
		np->tx_full = 0;
		wmb();
		netif_wake_queue(dev);
	}
}