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
typedef  int u32 ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct sk_buff {TYPE_1__ stats; } ;
struct ns83820 {int tx_done_idx; int tx_free_idx; int /*<<< orphan*/ * tx_descs; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  nr_tx_skbs; struct sk_buff** tx_skbs; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CMDSTS_ERR ; 
 int CMDSTS_LEN_MASK ; 
 int CMDSTS_OK ; 
 int CMDSTS_OWN ; 
 int DESC_BUFPTR ; 
 size_t DESC_CMDSTS ; 
 int DESC_SIZE ; 
 int NR_TX_DESC ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct ns83820* PRIV (struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_addr_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ netif_queue_stopped (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_start_queue (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ start_tx_okay (struct ns83820*) ; 

__attribute__((used)) static void do_tx_done(struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);
	u32 cmdsts, tx_done_idx;
	__le32 *desc;

	dprintk("do_tx_done(%p)\n", ndev);
	tx_done_idx = dev->tx_done_idx;
	desc = dev->tx_descs + (tx_done_idx * DESC_SIZE);

	dprintk("tx_done_idx=%d free_idx=%d cmdsts=%08x\n",
		tx_done_idx, dev->tx_free_idx, le32_to_cpu(desc[DESC_CMDSTS]));
	while ((tx_done_idx != dev->tx_free_idx) &&
	       !(CMDSTS_OWN & (cmdsts = le32_to_cpu(desc[DESC_CMDSTS]))) ) {
		struct sk_buff *skb;
		unsigned len;
		dma_addr_t addr;

		if (cmdsts & CMDSTS_ERR)
			ndev->stats.tx_errors++;
		if (cmdsts & CMDSTS_OK)
			ndev->stats.tx_packets++;
		if (cmdsts & CMDSTS_OK)
			ndev->stats.tx_bytes += cmdsts & 0xffff;

		dprintk("tx_done_idx=%d free_idx=%d cmdsts=%08x\n",
			tx_done_idx, dev->tx_free_idx, cmdsts);
		skb = dev->tx_skbs[tx_done_idx];
		dev->tx_skbs[tx_done_idx] = NULL;
		dprintk("done(%p)\n", skb);

		len = cmdsts & CMDSTS_LEN_MASK;
		addr = desc_addr_get(desc + DESC_BUFPTR);
		if (skb) {
			pci_unmap_single(dev->pci_dev,
					addr,
					len,
					PCI_DMA_TODEVICE);
			dev_consume_skb_irq(skb);
			atomic_dec(&dev->nr_tx_skbs);
		} else
			pci_unmap_page(dev->pci_dev,
					addr,
					len,
					PCI_DMA_TODEVICE);

		tx_done_idx = (tx_done_idx + 1) % NR_TX_DESC;
		dev->tx_done_idx = tx_done_idx;
		desc[DESC_CMDSTS] = cpu_to_le32(0);
		mb();
		desc = dev->tx_descs + (tx_done_idx * DESC_SIZE);
	}

	/* Allow network stack to resume queueing packets after we've
	 * finished transmitting at least 1/4 of the packets in the queue.
	 */
	if (netif_queue_stopped(ndev) && start_tx_okay(dev)) {
		dprintk("start_queue(%p)\n", ndev);
		netif_start_queue(ndev);
		netif_wake_queue(ndev);
	}
}