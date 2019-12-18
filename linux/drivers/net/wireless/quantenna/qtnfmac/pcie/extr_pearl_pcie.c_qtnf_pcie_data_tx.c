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
struct sk_buff {int len; TYPE_2__* dev; int /*<<< orphan*/  data; } ;
struct qtnf_pearl_tx_bd {void* info; void* addr_h; void* addr; } ;
struct qtnf_pcie_bus_priv {int tx_stopped; int tx_bd_w_index; int tx_bd_num; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_done_count; int /*<<< orphan*/  pdev; struct sk_buff** tx_skb; } ;
struct qtnf_pcie_pearl_state {int /*<<< orphan*/  pcie_reg_base; scalar_t__ tx_bd_pbase; struct qtnf_pearl_tx_bd* tx_bd_vbase; struct qtnf_pcie_bus_priv base; } ;
struct qtnf_bus {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int ENOMEM ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCIE_HDP_HOST_WR_DESC0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_HDP_HOST_WR_DESC0_H (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int QTN_HOST_HI32 (scalar_t__) ; 
 int QTN_HOST_LO32 (scalar_t__) ; 
 int QTN_PCIE_TX_DESC_LEN_MASK ; 
 int QTN_PCIE_TX_DESC_LEN_SHIFT ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 struct qtnf_pcie_pearl_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (TYPE_2__*) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 
 int /*<<< orphan*/  qtnf_pearl_data_tx_reclaim (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  qtnf_tx_queue_ready (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qtnf_pcie_data_tx(struct qtnf_bus *bus, struct sk_buff *skb)
{
	struct qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	struct qtnf_pcie_bus_priv *priv = &ps->base;
	dma_addr_t txbd_paddr, skb_paddr;
	struct qtnf_pearl_tx_bd *txbd;
	unsigned long flags;
	int len, i;
	u32 info;
	int ret = 0;

	spin_lock_irqsave(&priv->tx_lock, flags);

	if (!qtnf_tx_queue_ready(ps)) {
		if (skb->dev) {
			netif_tx_stop_all_queues(skb->dev);
			priv->tx_stopped = 1;
		}

		spin_unlock_irqrestore(&priv->tx_lock, flags);
		return NETDEV_TX_BUSY;
	}

	i = priv->tx_bd_w_index;
	priv->tx_skb[i] = skb;
	len = skb->len;

	skb_paddr = pci_map_single(priv->pdev, skb->data,
				   skb->len, PCI_DMA_TODEVICE);
	if (pci_dma_mapping_error(priv->pdev, skb_paddr)) {
		pr_err("skb DMA mapping error: %pad\n", &skb_paddr);
		ret = -ENOMEM;
		goto tx_done;
	}

	txbd = &ps->tx_bd_vbase[i];
	txbd->addr = cpu_to_le32(QTN_HOST_LO32(skb_paddr));
	txbd->addr_h = cpu_to_le32(QTN_HOST_HI32(skb_paddr));

	info = (len & QTN_PCIE_TX_DESC_LEN_MASK) << QTN_PCIE_TX_DESC_LEN_SHIFT;
	txbd->info = cpu_to_le32(info);

	/* sync up all descriptor updates before passing them to EP */
	dma_wmb();

	/* write new TX descriptor to PCIE_RX_FIFO on EP */
	txbd_paddr = ps->tx_bd_pbase + i * sizeof(struct qtnf_pearl_tx_bd);

#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	writel(QTN_HOST_HI32(txbd_paddr),
	       PCIE_HDP_HOST_WR_DESC0_H(ps->pcie_reg_base));
#endif
	writel(QTN_HOST_LO32(txbd_paddr),
	       PCIE_HDP_HOST_WR_DESC0(ps->pcie_reg_base));

	if (++i >= priv->tx_bd_num)
		i = 0;

	priv->tx_bd_w_index = i;

tx_done:
	if (ret && skb) {
		pr_err_ratelimited("drop skb\n");
		if (skb->dev)
			skb->dev->stats.tx_dropped++;
		dev_kfree_skb_any(skb);
	}

	priv->tx_done_count++;
	spin_unlock_irqrestore(&priv->tx_lock, flags);

	qtnf_pearl_data_tx_reclaim(ps);

	return NETDEV_TX_OK;
}