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
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct qtnf_pearl_rx_bd {int info; void* addr_h; void* addr; } ;
struct qtnf_pcie_bus_priv {size_t rx_bd_w_index; int /*<<< orphan*/  pdev; struct sk_buff** rx_skb; } ;
struct qtnf_pcie_pearl_state {int /*<<< orphan*/  pcie_reg_base; struct qtnf_pearl_rx_bd* rx_bd_vbase; struct qtnf_pcie_bus_priv base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCIE_HDP_HHBM_BUF_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_HDP_HHBM_BUF_PTR_H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_HDP_TX_HOST_Q_WR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 size_t QTN_HOST_HI32 (int /*<<< orphan*/ ) ; 
 size_t QTN_HOST_LO32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKB_BUF_SIZE ; 
 struct sk_buff* __netdev_alloc_skb_ip_align (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (size_t) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pearl_skb2rbd_attach(struct qtnf_pcie_pearl_state *ps, u16 index)
{
	struct qtnf_pcie_bus_priv *priv = &ps->base;
	struct qtnf_pearl_rx_bd *rxbd;
	struct sk_buff *skb;
	dma_addr_t paddr;

	skb = __netdev_alloc_skb_ip_align(NULL, SKB_BUF_SIZE, GFP_ATOMIC);
	if (!skb) {
		priv->rx_skb[index] = NULL;
		return -ENOMEM;
	}

	priv->rx_skb[index] = skb;
	rxbd = &ps->rx_bd_vbase[index];

	paddr = pci_map_single(priv->pdev, skb->data,
			       SKB_BUF_SIZE, PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(priv->pdev, paddr)) {
		pr_err("skb DMA mapping error: %pad\n", &paddr);
		return -ENOMEM;
	}

	/* keep rx skb paddrs in rx buffer descriptors for cleanup purposes */
	rxbd->addr = cpu_to_le32(QTN_HOST_LO32(paddr));
	rxbd->addr_h = cpu_to_le32(QTN_HOST_HI32(paddr));
	rxbd->info = 0x0;

	priv->rx_bd_w_index = index;

	/* sync up all descriptor updates */
	wmb();

#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	writel(QTN_HOST_HI32(paddr),
	       PCIE_HDP_HHBM_BUF_PTR_H(ps->pcie_reg_base));
#endif
	writel(QTN_HOST_LO32(paddr),
	       PCIE_HDP_HHBM_BUF_PTR(ps->pcie_reg_base));

	writel(index, PCIE_HDP_TX_HOST_Q_WR_PTR(ps->pcie_reg_base));
	return 0;
}