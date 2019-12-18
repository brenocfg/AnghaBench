#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  phydev; } ;
struct TYPE_6__ {int ndesc; TYPE_3__* desc; scalar_t__ done_idx; scalar_t__ proc_idx; } ;
struct TYPE_5__ {int ndesc; TYPE_3__* desc; scalar_t__ done_idx; scalar_t__ proc_idx; } ;
struct ave_private {TYPE_2__ rx; TYPE_1__ tx; int /*<<< orphan*/  napi_rx; int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {int /*<<< orphan*/ * skbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_DESC_STOP ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ave_desc_switch (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ave_dma_unmap (struct net_device*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ave_irq_disable_all (struct net_device*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ave_stop(struct net_device *ndev)
{
	struct ave_private *priv = netdev_priv(ndev);
	int entry;

	ave_irq_disable_all(ndev);
	disable_irq(priv->irq);
	free_irq(priv->irq, ndev);

	netif_tx_disable(ndev);
	phy_stop(ndev->phydev);
	napi_disable(&priv->napi_tx);
	napi_disable(&priv->napi_rx);

	ave_desc_switch(ndev, AVE_DESC_STOP);

	/* free Tx buffer */
	for (entry = 0; entry < priv->tx.ndesc; entry++) {
		if (!priv->tx.desc[entry].skbs)
			continue;

		ave_dma_unmap(ndev, &priv->tx.desc[entry], DMA_TO_DEVICE);
		dev_kfree_skb_any(priv->tx.desc[entry].skbs);
		priv->tx.desc[entry].skbs = NULL;
	}
	priv->tx.proc_idx = 0;
	priv->tx.done_idx = 0;

	/* free Rx buffer */
	for (entry = 0; entry < priv->rx.ndesc; entry++) {
		if (!priv->rx.desc[entry].skbs)
			continue;

		ave_dma_unmap(ndev, &priv->rx.desc[entry], DMA_FROM_DEVICE);
		dev_kfree_skb_any(priv->rx.desc[entry].skbs);
		priv->rx.desc[entry].skbs = NULL;
	}
	priv->rx.proc_idx = 0;
	priv->rx.done_idx = 0;

	kfree(priv->tx.desc);
	kfree(priv->rx.desc);

	return 0;
}