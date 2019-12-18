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
typedef  int u32 ;
struct sk_buff {scalar_t__ dev; int /*<<< orphan*/  len; } ;
struct qtnf_pearl_tx_bd {int /*<<< orphan*/  addr; int /*<<< orphan*/  addr_h; } ;
struct qtnf_pcie_bus_priv {int tx_bd_num; int tx_bd_r_index; int tx_reclaim_done; int /*<<< orphan*/  tx_reclaim_lock; int /*<<< orphan*/  tx_reclaim_req; struct sk_buff** tx_skb; scalar_t__ tx_stopped; int /*<<< orphan*/  pdev; } ;
struct qtnf_pcie_pearl_state {struct qtnf_pearl_tx_bd* tx_bd_vbase; int /*<<< orphan*/  pcie_reg_base; struct qtnf_pcie_bus_priv base; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ CIRC_CNT (int,int,int) ; 
 int /*<<< orphan*/  PCIE_HDP_RX0DMA_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  QTN_HOST_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_update_tx_stats (scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  qtnf_wake_all_queues (scalar_t__) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static void qtnf_pearl_data_tx_reclaim(struct qtnf_pcie_pearl_state *ps)
{
	struct qtnf_pcie_bus_priv *priv = &ps->base;
	struct qtnf_pearl_tx_bd *txbd;
	struct sk_buff *skb;
	unsigned long flags;
	dma_addr_t paddr;
	u32 tx_done_index;
	int count = 0;
	int i;

	spin_lock_irqsave(&priv->tx_reclaim_lock, flags);

	tx_done_index = readl(PCIE_HDP_RX0DMA_CNT(ps->pcie_reg_base))
			& (priv->tx_bd_num - 1);

	i = priv->tx_bd_r_index;

	while (CIRC_CNT(tx_done_index, i, priv->tx_bd_num)) {
		skb = priv->tx_skb[i];
		if (likely(skb)) {
			txbd = &ps->tx_bd_vbase[i];
			paddr = QTN_HOST_ADDR(le32_to_cpu(txbd->addr_h),
					      le32_to_cpu(txbd->addr));
			pci_unmap_single(priv->pdev, paddr, skb->len,
					 PCI_DMA_TODEVICE);

			if (skb->dev) {
				qtnf_update_tx_stats(skb->dev, skb);
				if (unlikely(priv->tx_stopped)) {
					qtnf_wake_all_queues(skb->dev);
					priv->tx_stopped = 0;
				}
			}

			dev_kfree_skb_any(skb);
		}

		priv->tx_skb[i] = NULL;
		count++;

		if (++i >= priv->tx_bd_num)
			i = 0;
	}

	priv->tx_reclaim_done += count;
	priv->tx_reclaim_req++;
	priv->tx_bd_r_index = i;

	spin_unlock_irqrestore(&priv->tx_reclaim_lock, flags);
}