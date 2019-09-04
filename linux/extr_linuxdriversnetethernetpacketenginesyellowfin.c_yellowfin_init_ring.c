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
struct yellowfin_private {int rx_buf_sz; int rx_ring_dma; unsigned int dirty_rx; int tx_ring_dma; int /*<<< orphan*/ * tx_status; int /*<<< orphan*/ * tx_tail_desc; TYPE_2__* tx_ring; int /*<<< orphan*/ ** tx_skbuff; TYPE_1__* rx_ring; struct sk_buff** rx_skbuff; int /*<<< orphan*/  pci_dev; scalar_t__ dirty_tx; scalar_t__ cur_tx; scalar_t__ cur_rx; scalar_t__ tx_full; } ;
struct yellowfin_desc {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int mtu; } ;
struct TYPE_4__ {void* dbdma_cmd; void* branch_addr; } ;
struct TYPE_3__ {void* dbdma_cmd; void* addr; void* branch_addr; } ;

/* Variables and functions */
 int BRANCH_ALWAYS ; 
 int CMD_RX_BUF ; 
 int CMD_STOP ; 
 int ENOMEM ; 
 int INTR_ALWAYS ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct yellowfin_private* netdev_priv (struct net_device*) ; 
 int pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int yellowfin_init_ring(struct net_device *dev)
{
	struct yellowfin_private *yp = netdev_priv(dev);
	int i, j;

	yp->tx_full = 0;
	yp->cur_rx = yp->cur_tx = 0;
	yp->dirty_tx = 0;

	yp->rx_buf_sz = (dev->mtu <= 1500 ? PKT_BUF_SZ : dev->mtu + 32);

	for (i = 0; i < RX_RING_SIZE; i++) {
		yp->rx_ring[i].dbdma_cmd =
			cpu_to_le32(CMD_RX_BUF | INTR_ALWAYS | yp->rx_buf_sz);
		yp->rx_ring[i].branch_addr = cpu_to_le32(yp->rx_ring_dma +
			((i+1)%RX_RING_SIZE)*sizeof(struct yellowfin_desc));
	}

	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb = netdev_alloc_skb(dev, yp->rx_buf_sz + 2);
		yp->rx_skbuff[i] = skb;
		if (skb == NULL)
			break;
		skb_reserve(skb, 2);	/* 16 byte align the IP header. */
		yp->rx_ring[i].addr = cpu_to_le32(pci_map_single(yp->pci_dev,
			skb->data, yp->rx_buf_sz, PCI_DMA_FROMDEVICE));
	}
	if (i != RX_RING_SIZE) {
		for (j = 0; j < i; j++)
			dev_kfree_skb(yp->rx_skbuff[j]);
		return -ENOMEM;
	}
	yp->rx_ring[i-1].dbdma_cmd = cpu_to_le32(CMD_STOP);
	yp->dirty_rx = (unsigned int)(i - RX_RING_SIZE);

#define NO_TXSTATS
#ifdef NO_TXSTATS
	/* In this mode the Tx ring needs only a single descriptor. */
	for (i = 0; i < TX_RING_SIZE; i++) {
		yp->tx_skbuff[i] = NULL;
		yp->tx_ring[i].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->tx_ring[i].branch_addr = cpu_to_le32(yp->tx_ring_dma +
			((i+1)%TX_RING_SIZE)*sizeof(struct yellowfin_desc));
	}
	/* Wrap ring */
	yp->tx_ring[--i].dbdma_cmd = cpu_to_le32(CMD_STOP | BRANCH_ALWAYS);
#else
{
	/* Tx ring needs a pair of descriptors, the second for the status. */
	for (i = 0; i < TX_RING_SIZE; i++) {
		j = 2*i;
		yp->tx_skbuff[i] = 0;
		/* Branch on Tx error. */
		yp->tx_ring[j].dbdma_cmd = cpu_to_le32(CMD_STOP);
		yp->tx_ring[j].branch_addr = cpu_to_le32(yp->tx_ring_dma +
			(j+1)*sizeof(struct yellowfin_desc));
		j++;
		if (yp->flags & FullTxStatus) {
			yp->tx_ring[j].dbdma_cmd =
				cpu_to_le32(CMD_TXSTATUS | sizeof(*yp->tx_status));
			yp->tx_ring[j].request_cnt = sizeof(*yp->tx_status);
			yp->tx_ring[j].addr = cpu_to_le32(yp->tx_status_dma +
				i*sizeof(struct tx_status_words));
		} else {
			/* Symbios chips write only tx_errs word. */
			yp->tx_ring[j].dbdma_cmd =
				cpu_to_le32(CMD_TXSTATUS | INTR_ALWAYS | 2);
			yp->tx_ring[j].request_cnt = 2;
			/* Om pade ummmmm... */
			yp->tx_ring[j].addr = cpu_to_le32(yp->tx_status_dma +
				i*sizeof(struct tx_status_words) +
				&(yp->tx_status[0].tx_errs) -
				&(yp->tx_status[0]));
		}
		yp->tx_ring[j].branch_addr = cpu_to_le32(yp->tx_ring_dma +
			((j+1)%(2*TX_RING_SIZE))*sizeof(struct yellowfin_desc));
	}
	/* Wrap ring */
	yp->tx_ring[++j].dbdma_cmd |= cpu_to_le32(BRANCH_ALWAYS | INTR_ALWAYS);
}
#endif
	yp->tx_tail_desc = &yp->tx_status[0];
	return 0;
}