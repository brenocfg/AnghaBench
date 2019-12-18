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
struct tx_desc {int dummy; } ;
struct net_device {int dummy; } ;
struct hip04_priv {int /*<<< orphan*/  tx_desc_dma; int /*<<< orphan*/  tx_desc; scalar_t__* tx_skb; scalar_t__* rx_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RX_DESC_NUM ; 
 int TX_DESC_NUM ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_free_frag (scalar_t__) ; 

__attribute__((used)) static void hip04_free_ring(struct net_device *ndev, struct device *d)
{
	struct hip04_priv *priv = netdev_priv(ndev);
	int i;

	for (i = 0; i < RX_DESC_NUM; i++)
		if (priv->rx_buf[i])
			skb_free_frag(priv->rx_buf[i]);

	for (i = 0; i < TX_DESC_NUM; i++)
		if (priv->tx_skb[i])
			dev_kfree_skb_any(priv->tx_skb[i]);

	dma_free_coherent(d, TX_DESC_NUM * sizeof(struct tx_desc),
			  priv->tx_desc, priv->tx_desc_dma);
}