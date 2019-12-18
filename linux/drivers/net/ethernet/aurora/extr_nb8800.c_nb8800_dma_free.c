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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct nb8800_priv {int /*<<< orphan*/ * tx_descs; int /*<<< orphan*/  tx_desc_dma; int /*<<< orphan*/ * rx_descs; int /*<<< orphan*/  rx_desc_dma; TYPE_2__* tx_bufs; TYPE_2__* rx_bufs; } ;
struct TYPE_4__ {int /*<<< orphan*/  skb; scalar_t__ page; } ;

/* Variables and functions */
 unsigned int RX_DESC_COUNT ; 
 int /*<<< orphan*/  RX_DESC_SIZE ; 
 unsigned int TX_DESC_COUNT ; 
 int /*<<< orphan*/  TX_DESC_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 

__attribute__((used)) static void nb8800_dma_free(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	unsigned int i;

	if (priv->rx_bufs) {
		for (i = 0; i < RX_DESC_COUNT; i++)
			if (priv->rx_bufs[i].page)
				put_page(priv->rx_bufs[i].page);

		kfree(priv->rx_bufs);
		priv->rx_bufs = NULL;
	}

	if (priv->tx_bufs) {
		for (i = 0; i < TX_DESC_COUNT; i++)
			kfree_skb(priv->tx_bufs[i].skb);

		kfree(priv->tx_bufs);
		priv->tx_bufs = NULL;
	}

	if (priv->rx_descs) {
		dma_free_coherent(dev->dev.parent, RX_DESC_SIZE, priv->rx_descs,
				  priv->rx_desc_dma);
		priv->rx_descs = NULL;
	}

	if (priv->tx_descs) {
		dma_free_coherent(dev->dev.parent, TX_DESC_SIZE, priv->tx_descs,
				  priv->tx_desc_dma);
		priv->tx_descs = NULL;
	}
}