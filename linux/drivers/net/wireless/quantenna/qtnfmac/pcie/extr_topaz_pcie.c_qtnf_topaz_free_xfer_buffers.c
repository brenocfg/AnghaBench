#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct qtnf_topaz_tx_bd {scalar_t__ info; scalar_t__ addr; } ;
struct qtnf_topaz_rx_bd {scalar_t__ info; scalar_t__ addr; } ;
struct qtnf_pcie_bus_priv {int rx_bd_num; int tx_bd_num; struct sk_buff** tx_skb; int /*<<< orphan*/  pdev; struct sk_buff** rx_skb; } ;
struct qtnf_pcie_topaz_state {struct qtnf_topaz_tx_bd* tx_bd_vbase; struct qtnf_topaz_rx_bd* rx_bd_vbase; struct qtnf_pcie_bus_priv base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  QTN_HOST_ADDR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKB_BUF_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qtnf_topaz_free_xfer_buffers(struct qtnf_pcie_topaz_state *ts)
{
	struct qtnf_pcie_bus_priv *priv = &ts->base;
	struct qtnf_topaz_rx_bd *rxbd;
	struct qtnf_topaz_tx_bd *txbd;
	struct sk_buff *skb;
	dma_addr_t paddr;
	int i;

	/* free rx buffers */
	for (i = 0; i < priv->rx_bd_num; i++) {
		if (priv->rx_skb && priv->rx_skb[i]) {
			rxbd = &ts->rx_bd_vbase[i];
			skb = priv->rx_skb[i];
			paddr = QTN_HOST_ADDR(0x0, le32_to_cpu(rxbd->addr));
			pci_unmap_single(priv->pdev, paddr, SKB_BUF_SIZE,
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb_any(skb);
			priv->rx_skb[i] = NULL;
			rxbd->addr = 0;
			rxbd->info = 0;
		}
	}

	/* free tx buffers */
	for (i = 0; i < priv->tx_bd_num; i++) {
		if (priv->tx_skb && priv->tx_skb[i]) {
			txbd = &ts->tx_bd_vbase[i];
			skb = priv->tx_skb[i];
			paddr = QTN_HOST_ADDR(0x0, le32_to_cpu(txbd->addr));
			pci_unmap_single(priv->pdev, paddr, SKB_BUF_SIZE,
					 PCI_DMA_TODEVICE);
			dev_kfree_skb_any(skb);
			priv->tx_skb[i] = NULL;
			txbd->addr = 0;
			txbd->info = 0;
		}
	}
}