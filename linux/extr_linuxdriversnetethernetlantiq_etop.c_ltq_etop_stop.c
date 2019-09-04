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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ltq_etop_priv {struct ltq_etop_chan* ch; } ;
struct ltq_etop_chan {int /*<<< orphan*/  dma; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RX (int) ; 
 int /*<<< orphan*/  IS_TX (int) ; 
 int MAX_DMA_CHAN ; 
 int /*<<< orphan*/  ltq_dma_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ltq_etop_stop(struct net_device *dev)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	int i;

	netif_tx_stop_all_queues(dev);
	phy_stop(dev->phydev);
	for (i = 0; i < MAX_DMA_CHAN; i++) {
		struct ltq_etop_chan *ch = &priv->ch[i];

		if (!IS_RX(i) && !IS_TX(i))
			continue;
		napi_disable(&ch->napi);
		ltq_dma_close(&ch->dma);
	}
	return 0;
}