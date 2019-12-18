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
struct sk_buff {int dummy; } ;
struct gem_txd {scalar_t__ control_word; scalar_t__ buffer; } ;
struct gem_rxd {scalar_t__ buffer; scalar_t__ status_word; } ;
struct gem_init_block {struct gem_txd* txd; struct gem_rxd* rxd; } ;
struct gem {int /*<<< orphan*/  pdev; struct sk_buff** tx_skbs; struct sk_buff** rx_skbs; struct gem_init_block* init_block; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int RX_BUF_ALLOC_SIZE (struct gem*) ; 
 int RX_RING_SIZE ; 
 int TXDCTRL_BUFSZ ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int le64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void gem_clean_rings(struct gem *gp)
{
	struct gem_init_block *gb = gp->init_block;
	struct sk_buff *skb;
	int i;
	dma_addr_t dma_addr;

	for (i = 0; i < RX_RING_SIZE; i++) {
		struct gem_rxd *rxd;

		rxd = &gb->rxd[i];
		if (gp->rx_skbs[i] != NULL) {
			skb = gp->rx_skbs[i];
			dma_addr = le64_to_cpu(rxd->buffer);
			pci_unmap_page(gp->pdev, dma_addr,
				       RX_BUF_ALLOC_SIZE(gp),
				       PCI_DMA_FROMDEVICE);
			dev_kfree_skb_any(skb);
			gp->rx_skbs[i] = NULL;
		}
		rxd->status_word = 0;
		dma_wmb();
		rxd->buffer = 0;
	}

	for (i = 0; i < TX_RING_SIZE; i++) {
		if (gp->tx_skbs[i] != NULL) {
			struct gem_txd *txd;
			int frag;

			skb = gp->tx_skbs[i];
			gp->tx_skbs[i] = NULL;

			for (frag = 0; frag <= skb_shinfo(skb)->nr_frags; frag++) {
				int ent = i & (TX_RING_SIZE - 1);

				txd = &gb->txd[ent];
				dma_addr = le64_to_cpu(txd->buffer);
				pci_unmap_page(gp->pdev, dma_addr,
					       le64_to_cpu(txd->control_word) &
					       TXDCTRL_BUFSZ, PCI_DMA_TODEVICE);

				if (frag != skb_shinfo(skb)->nr_frags)
					i++;
			}
			dev_kfree_skb_any(skb);
		}
	}
}