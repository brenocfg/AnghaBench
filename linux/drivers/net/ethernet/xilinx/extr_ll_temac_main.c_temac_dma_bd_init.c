#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct temac_local {int tx_bd_p; int rx_bd_p; int tx_chnl_ctrl; int rx_chnl_ctrl; int /*<<< orphan*/  (* dma_out ) (struct temac_local*,int /*<<< orphan*/ ,int) ;scalar_t__ rx_bd_ci; scalar_t__ tx_bd_tail; scalar_t__ tx_bd_next; scalar_t__ tx_bd_ci; TYPE_2__* rx_bd_v; struct sk_buff** rx_skb; TYPE_1__* tx_bd_v; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_3__ dev; } ;
typedef  int dma_addr_t ;
struct TYPE_5__ {void* app0; void* len; void* phys; void* next; } ;
struct TYPE_4__ {void* next; } ;

/* Variables and functions */
 int CHNL_CTRL_IRQ_COAL_EN ; 
 int CHNL_CTRL_IRQ_DLY_EN ; 
 int CHNL_CTRL_IRQ_EN ; 
 int CHNL_CTRL_IRQ_ERR_EN ; 
 int CHNL_CTRL_IRQ_IOE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RX_BD_NUM ; 
 int /*<<< orphan*/  RX_CHNL_CTRL ; 
 int /*<<< orphan*/  RX_CURDESC_PTR ; 
 int /*<<< orphan*/  RX_TAILDESC_PTR ; 
 int STS_CTRL_APP0_IRQONEND ; 
 int TX_BD_NUM ; 
 int /*<<< orphan*/  TX_CHNL_CTRL ; 
 int /*<<< orphan*/  TX_CURDESC_PTR ; 
 int XTE_MAX_JUMBO_FRAME_SIZE ; 
 void* cpu_to_be32 (int) ; 
 struct sk_buff** devm_kcalloc (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  temac_dma_bd_release (struct net_device*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int temac_dma_bd_init(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	struct sk_buff *skb;
	dma_addr_t skb_dma_addr;
	int i;

	lp->rx_skb = devm_kcalloc(&ndev->dev, RX_BD_NUM, sizeof(*lp->rx_skb),
				  GFP_KERNEL);
	if (!lp->rx_skb)
		goto out;

	/* allocate the tx and rx ring buffer descriptors. */
	/* returns a virtual address and a physical address. */
	lp->tx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					 sizeof(*lp->tx_bd_v) * TX_BD_NUM,
					 &lp->tx_bd_p, GFP_KERNEL);
	if (!lp->tx_bd_v)
		goto out;

	lp->rx_bd_v = dma_alloc_coherent(ndev->dev.parent,
					 sizeof(*lp->rx_bd_v) * RX_BD_NUM,
					 &lp->rx_bd_p, GFP_KERNEL);
	if (!lp->rx_bd_v)
		goto out;

	for (i = 0; i < TX_BD_NUM; i++) {
		lp->tx_bd_v[i].next = cpu_to_be32(lp->tx_bd_p
				+ sizeof(*lp->tx_bd_v) * ((i + 1) % TX_BD_NUM));
	}

	for (i = 0; i < RX_BD_NUM; i++) {
		lp->rx_bd_v[i].next = cpu_to_be32(lp->rx_bd_p
				+ sizeof(*lp->rx_bd_v) * ((i + 1) % RX_BD_NUM));

		skb = netdev_alloc_skb_ip_align(ndev,
						XTE_MAX_JUMBO_FRAME_SIZE);
		if (!skb)
			goto out;

		lp->rx_skb[i] = skb;
		/* returns physical address of skb->data */
		skb_dma_addr = dma_map_single(ndev->dev.parent, skb->data,
					      XTE_MAX_JUMBO_FRAME_SIZE,
					      DMA_FROM_DEVICE);
		lp->rx_bd_v[i].phys = cpu_to_be32(skb_dma_addr);
		lp->rx_bd_v[i].len = cpu_to_be32(XTE_MAX_JUMBO_FRAME_SIZE);
		lp->rx_bd_v[i].app0 = cpu_to_be32(STS_CTRL_APP0_IRQONEND);
	}

	/* Configure DMA channel (irq setup) */
	lp->dma_out(lp, TX_CHNL_CTRL, lp->tx_chnl_ctrl |
		    0x00000400 | // Use 1 Bit Wide Counters. Currently Not Used!
		    CHNL_CTRL_IRQ_EN | CHNL_CTRL_IRQ_ERR_EN |
		    CHNL_CTRL_IRQ_DLY_EN | CHNL_CTRL_IRQ_COAL_EN);
	lp->dma_out(lp, RX_CHNL_CTRL, lp->rx_chnl_ctrl |
		    CHNL_CTRL_IRQ_IOE |
		    CHNL_CTRL_IRQ_EN | CHNL_CTRL_IRQ_ERR_EN |
		    CHNL_CTRL_IRQ_DLY_EN | CHNL_CTRL_IRQ_COAL_EN);

	/* Init descriptor indexes */
	lp->tx_bd_ci = 0;
	lp->tx_bd_next = 0;
	lp->tx_bd_tail = 0;
	lp->rx_bd_ci = 0;

	/* Enable RX DMA transfers */
	wmb();
	lp->dma_out(lp, RX_CURDESC_PTR,  lp->rx_bd_p);
	lp->dma_out(lp, RX_TAILDESC_PTR,
		       lp->rx_bd_p + (sizeof(*lp->rx_bd_v) * (RX_BD_NUM - 1)));

	/* Prepare for TX DMA transfer */
	lp->dma_out(lp, TX_CURDESC_PTR, lp->tx_bd_p);

	return 0;

out:
	temac_dma_bd_release(ndev);
	return -ENOMEM;
}