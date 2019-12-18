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
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct bcm_enet_priv {int rx_ring_size; int irq_tx; int irq_rx; int /*<<< orphan*/  tx_desc_dma; struct bcm_enet_desc* tx_desc_cpu; int /*<<< orphan*/  tx_desc_alloc_size; int /*<<< orphan*/  rx_desc_dma; struct bcm_enet_desc* rx_desc_cpu; int /*<<< orphan*/  rx_desc_alloc_size; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  rx_skb_size; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  rx_timeout; int /*<<< orphan*/  napi; int /*<<< orphan*/  swphy_poll; TYPE_1__* pdev; } ;
struct bcm_enet_desc {int /*<<< orphan*/  address; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ENETDMAC_IRMASK ; 
 int /*<<< orphan*/  bcm_enet_disable_dma (struct bcm_enet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_enet_tx_reclaim (struct net_device*,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,struct bcm_enet_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_dmac_writel (struct bcm_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int bcm_enetsw_stop(struct net_device *dev)
{
	struct bcm_enet_priv *priv;
	struct device *kdev;
	int i;

	priv = netdev_priv(dev);
	kdev = &priv->pdev->dev;

	del_timer_sync(&priv->swphy_poll);
	netif_stop_queue(dev);
	napi_disable(&priv->napi);
	del_timer_sync(&priv->rx_timeout);

	/* mask all interrupts */
	enet_dmac_writel(priv, 0, ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_writel(priv, 0, ENETDMAC_IRMASK, priv->tx_chan);

	/* disable dma & mac */
	bcm_enet_disable_dma(priv, priv->tx_chan);
	bcm_enet_disable_dma(priv, priv->rx_chan);

	/* force reclaim of all tx buffers */
	bcm_enet_tx_reclaim(dev, 1);

	/* free the rx skb ring */
	for (i = 0; i < priv->rx_ring_size; i++) {
		struct bcm_enet_desc *desc;

		if (!priv->rx_skb[i])
			continue;

		desc = &priv->rx_desc_cpu[i];
		dma_unmap_single(kdev, desc->address, priv->rx_skb_size,
				 DMA_FROM_DEVICE);
		kfree_skb(priv->rx_skb[i]);
	}

	/* free remaining allocated memory */
	kfree(priv->rx_skb);
	kfree(priv->tx_skb);
	dma_free_coherent(kdev, priv->rx_desc_alloc_size,
			  priv->rx_desc_cpu, priv->rx_desc_dma);
	dma_free_coherent(kdev, priv->tx_desc_alloc_size,
			  priv->tx_desc_cpu, priv->tx_desc_dma);
	if (priv->irq_tx != -1)
		free_irq(priv->irq_tx, dev);
	free_irq(priv->irq_rx, dev);

	return 0;
}