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
struct qtnf_pearl_tx_bd {int dummy; } ;
struct qtnf_pearl_rx_bd {int dummy; } ;
struct qtnf_pcie_bus_priv {int tx_bd_num; int rx_bd_num; scalar_t__ tx_bd_w_index; scalar_t__ tx_bd_r_index; TYPE_1__* pdev; } ;
struct qtnf_pcie_pearl_state {int bd_table_paddr; int bd_table_len; int tx_bd_pbase; int rx_bd_pbase; int /*<<< orphan*/  pcie_reg_base; void* rx_bd_vbase; void* tx_bd_vbase; void* bd_table_vaddr; struct qtnf_pcie_bus_priv base; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCIE_HDP_TX_HOST_Q_BASE_H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_HDP_TX_HOST_Q_BASE_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_HDP_TX_HOST_Q_SZ_CTRL (int /*<<< orphan*/ ) ; 
 int QTN_HOST_HI32 (int) ; 
 int QTN_HOST_LO32 (int) ; 
 void* dmam_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,int*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pearl_alloc_bd_table(struct qtnf_pcie_pearl_state *ps)
{
	struct qtnf_pcie_bus_priv *priv = &ps->base;
	dma_addr_t paddr;
	void *vaddr;
	int len;

	len = priv->tx_bd_num * sizeof(struct qtnf_pearl_tx_bd) +
		priv->rx_bd_num * sizeof(struct qtnf_pearl_rx_bd);

	vaddr = dmam_alloc_coherent(&priv->pdev->dev, len, &paddr, GFP_KERNEL);
	if (!vaddr)
		return -ENOMEM;

	/* tx bd */

	memset(vaddr, 0, len);

	ps->bd_table_vaddr = vaddr;
	ps->bd_table_paddr = paddr;
	ps->bd_table_len = len;

	ps->tx_bd_vbase = vaddr;
	ps->tx_bd_pbase = paddr;

	pr_debug("TX descriptor table: vaddr=0x%p paddr=%pad\n", vaddr, &paddr);

	priv->tx_bd_r_index = 0;
	priv->tx_bd_w_index = 0;

	/* rx bd */

	vaddr = ((struct qtnf_pearl_tx_bd *)vaddr) + priv->tx_bd_num;
	paddr += priv->tx_bd_num * sizeof(struct qtnf_pearl_tx_bd);

	ps->rx_bd_vbase = vaddr;
	ps->rx_bd_pbase = paddr;

#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	writel(QTN_HOST_HI32(paddr),
	       PCIE_HDP_TX_HOST_Q_BASE_H(ps->pcie_reg_base));
#endif
	writel(QTN_HOST_LO32(paddr),
	       PCIE_HDP_TX_HOST_Q_BASE_L(ps->pcie_reg_base));
	writel(priv->rx_bd_num | (sizeof(struct qtnf_pearl_rx_bd)) << 16,
	       PCIE_HDP_TX_HOST_Q_SZ_CTRL(ps->pcie_reg_base));

	pr_debug("RX descriptor table: vaddr=0x%p paddr=%pad\n", vaddr, &paddr);

	return 0;
}