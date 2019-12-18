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
struct sk_buff {int dummy; } ;
struct nixge_priv {int /*<<< orphan*/  tx_bd_p; int /*<<< orphan*/ * tx_bd_v; scalar_t__ tx_skb; int /*<<< orphan*/  rx_bd_p; int /*<<< orphan*/ * rx_bd_v; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  NIXGE_MAX_JUMBO_FRAME_SIZE ; 
 int RX_BD_NUM ; 
 int TX_BD_NUM ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nixge_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ nixge_hw_dma_bd_get_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys ; 
 int /*<<< orphan*/  sw_id_offset ; 

__attribute__((used)) static void nixge_hw_dma_bd_release(struct net_device *ndev)
{
	struct nixge_priv *priv = netdev_priv(ndev);
	dma_addr_t phys_addr;
	struct sk_buff *skb;
	int i;

	for (i = 0; i < RX_BD_NUM; i++) {
		phys_addr = nixge_hw_dma_bd_get_addr(&priv->rx_bd_v[i],
						     phys);

		dma_unmap_single(ndev->dev.parent, phys_addr,
				 NIXGE_MAX_JUMBO_FRAME_SIZE,
				 DMA_FROM_DEVICE);

		skb = (struct sk_buff *)(uintptr_t)
			nixge_hw_dma_bd_get_addr(&priv->rx_bd_v[i],
						 sw_id_offset);
		dev_kfree_skb(skb);
	}

	if (priv->rx_bd_v)
		dma_free_coherent(ndev->dev.parent,
				  sizeof(*priv->rx_bd_v) * RX_BD_NUM,
				  priv->rx_bd_v,
				  priv->rx_bd_p);

	if (priv->tx_skb)
		devm_kfree(ndev->dev.parent, priv->tx_skb);

	if (priv->tx_bd_v)
		dma_free_coherent(ndev->dev.parent,
				  sizeof(*priv->tx_bd_v) * TX_BD_NUM,
				  priv->tx_bd_v,
				  priv->tx_bd_p);
}