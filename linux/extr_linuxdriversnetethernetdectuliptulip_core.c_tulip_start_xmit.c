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
typedef  int u32 ;
struct tulip_private {int cur_tx; int dirty_tx; int /*<<< orphan*/  lock; scalar_t__ base_addr; TYPE_2__* tx_ring; TYPE_1__* tx_buffers; int /*<<< orphan*/  pdev; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int dma_addr_t ;
struct TYPE_4__ {void* status; void* length; void* buffer1; } ;
struct TYPE_3__ {int mapping; struct sk_buff* skb; } ;

/* Variables and functions */
 scalar_t__ CSR1 ; 
 int DESC_RING_WRAP ; 
 int DescOwned ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_RING_SIZE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct tulip_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t
tulip_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct tulip_private *tp = netdev_priv(dev);
	int entry;
	u32 flag;
	dma_addr_t mapping;
	unsigned long flags;

	spin_lock_irqsave(&tp->lock, flags);

	/* Calculate the next Tx descriptor entry. */
	entry = tp->cur_tx % TX_RING_SIZE;

	tp->tx_buffers[entry].skb = skb;
	mapping = pci_map_single(tp->pdev, skb->data,
				 skb->len, PCI_DMA_TODEVICE);
	tp->tx_buffers[entry].mapping = mapping;
	tp->tx_ring[entry].buffer1 = cpu_to_le32(mapping);

	if (tp->cur_tx - tp->dirty_tx < TX_RING_SIZE/2) {/* Typical path */
		flag = 0x60000000; /* No interrupt */
	} else if (tp->cur_tx - tp->dirty_tx == TX_RING_SIZE/2) {
		flag = 0xe0000000; /* Tx-done intr. */
	} else if (tp->cur_tx - tp->dirty_tx < TX_RING_SIZE - 2) {
		flag = 0x60000000; /* No Tx-done intr. */
	} else {		/* Leave room for set_rx_mode() to fill entries. */
		flag = 0xe0000000; /* Tx-done intr. */
		netif_stop_queue(dev);
	}
	if (entry == TX_RING_SIZE-1)
		flag = 0xe0000000 | DESC_RING_WRAP;

	tp->tx_ring[entry].length = cpu_to_le32(skb->len | flag);
	/* if we were using Transmit Automatic Polling, we would need a
	 * wmb() here. */
	tp->tx_ring[entry].status = cpu_to_le32(DescOwned);
	wmb();

	tp->cur_tx++;

	/* Trigger an immediate transmit demand. */
	iowrite32(0, tp->base_addr + CSR1);

	spin_unlock_irqrestore(&tp->lock, flags);

	return NETDEV_TX_OK;
}