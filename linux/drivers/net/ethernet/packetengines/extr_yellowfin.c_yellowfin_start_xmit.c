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
struct yellowfin_private {int cur_tx; scalar_t__ dirty_tx; int tx_full; scalar_t__ base; TYPE_1__* tx_ring; int /*<<< orphan*/  pci_dev; struct sk_buff** tx_skbuff; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int request_cnt; void* dbdma_cmd; void* addr; scalar_t__ result_status; } ;

/* Variables and functions */
 int BRANCH_ALWAYS ; 
 int BRANCH_IFTRUE ; 
 int CMD_STOP ; 
 int CMD_TX_PKT ; 
 int INTR_ALWAYS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ TX_QUEUE_SIZE ; 
 int TX_RING_SIZE ; 
 scalar_t__ TxCtrl ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ gx_fix ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_printk (int /*<<< orphan*/ ,struct net_device*,char*,scalar_t__,unsigned int) ; 
 struct yellowfin_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int pci_map_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_padto (struct sk_buff*,int) ; 
 int yellowfin_debug ; 

__attribute__((used)) static netdev_tx_t yellowfin_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
	struct yellowfin_private *yp = netdev_priv(dev);
	unsigned entry;
	int len = skb->len;

	netif_stop_queue (dev);

	/* Note: Ordering is important here, set the field with the
	   "ownership" bit last, and only then increment cur_tx. */

	/* Calculate the next Tx descriptor entry. */
	entry = yp->cur_tx % TX_RING_SIZE;

	if (gx_fix) {	/* Note: only works for paddable protocols e.g.  IP. */
		int cacheline_end = ((unsigned long)skb->data + skb->len) % 32;
		/* Fix GX chipset errata. */
		if (cacheline_end > 24  || cacheline_end == 0) {
			len = skb->len + 32 - cacheline_end + 1;
			if (skb_padto(skb, len)) {
				yp->tx_skbuff[entry] = NULL;
				netif_wake_queue(dev);
				return NETDEV_TX_OK;
			}
		}
	}
	yp->tx_skbuff[entry] = skb;

#ifdef NO_TXSTATS
	yp->tx_ring[entry].addr = cpu_to_le32(pci_map_single(yp->pci_dev,
		skb->data, len, PCI_DMA_TODEVICE));
	yp->tx_ring[entry].result_status = 0;
	if (entry >= TX_RING_SIZE-1) {
		/* New stop command. */
		yp->tx_ring[0].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->tx_ring[TX_RING_SIZE-1].dbdma_cmd =
			cpu_to_le32(CMD_TX_PKT|BRANCH_ALWAYS | len);
	} else {
		yp->tx_ring[entry+1].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->tx_ring[entry].dbdma_cmd =
			cpu_to_le32(CMD_TX_PKT | BRANCH_IFTRUE | len);
	}
	yp->cur_tx++;
#else
	yp->tx_ring[entry<<1].request_cnt = len;
	yp->tx_ring[entry<<1].addr = cpu_to_le32(pci_map_single(yp->pci_dev,
		skb->data, len, PCI_DMA_TODEVICE));
	/* The input_last (status-write) command is constant, but we must
	   rewrite the subsequent 'stop' command. */

	yp->cur_tx++;
	{
		unsigned next_entry = yp->cur_tx % TX_RING_SIZE;
		yp->tx_ring[next_entry<<1].dbdma_cmd = cpu_to_le32(CMD_STOP);
	}
	/* Final step -- overwrite the old 'stop' command. */

	yp->tx_ring[entry<<1].dbdma_cmd =
		cpu_to_le32( ((entry % 6) == 0 ? CMD_TX_PKT|INTR_ALWAYS|BRANCH_IFTRUE :
					  CMD_TX_PKT | BRANCH_IFTRUE) | len);
#endif

	/* Non-x86 Todo: explicitly flush cache lines here. */

	/* Wake the potentially-idle transmit channel. */
	iowrite32(0x10001000, yp->base + TxCtrl);

	if (yp->cur_tx - yp->dirty_tx < TX_QUEUE_SIZE)
		netif_start_queue (dev);		/* Typical path */
	else
		yp->tx_full = 1;

	if (yellowfin_debug > 4) {
		netdev_printk(KERN_DEBUG, dev, "Yellowfin transmit frame #%d queued in slot %d\n",
			      yp->cur_tx, entry);
	}
	return NETDEV_TX_OK;
}