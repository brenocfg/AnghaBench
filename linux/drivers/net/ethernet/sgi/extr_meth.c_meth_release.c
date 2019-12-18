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
struct net_device {int /*<<< orphan*/  irq; } ;
struct meth_private {int dma_ctrl; } ;
struct TYPE_3__ {int dma_ctrl; } ;
struct TYPE_4__ {TYPE_1__ eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int METH_DMA_RX_EN ; 
 int METH_DMA_RX_INT_EN ; 
 int METH_DMA_TX_EN ; 
 int METH_DMA_TX_INT_EN ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 TYPE_2__* mace ; 
 int /*<<< orphan*/  meth_free_rx_ring (struct meth_private*) ; 
 int /*<<< orphan*/  meth_free_tx_ring (struct meth_private*) ; 
 struct meth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int meth_release(struct net_device *dev)
{
	struct meth_private *priv = netdev_priv(dev);

	DPRINTK("Stopping queue\n");
	netif_stop_queue(dev); /* can't transmit any more */
	/* shut down DMA */
	priv->dma_ctrl &= ~(METH_DMA_TX_EN | METH_DMA_TX_INT_EN |
			    METH_DMA_RX_EN | METH_DMA_RX_INT_EN);
	mace->eth.dma_ctrl = priv->dma_ctrl;
	free_irq(dev->irq, dev);
	meth_free_tx_ring(priv);
	meth_free_rx_ring(priv);

	return 0;
}