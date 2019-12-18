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
struct ltq_etop_chan {int /*<<< orphan*/  napi; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_RX (int) ; 
 int /*<<< orphan*/  IS_TX (int) ; 
 int MAX_DMA_CHAN ; 
 int /*<<< orphan*/  ltq_dma_enable_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltq_dma_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ltq_etop_open(struct net_device *dev)
{
	struct ltq_etop_priv *priv = netdev_priv(dev);
	int i;

	for (i = 0; i < MAX_DMA_CHAN; i++) {
		struct ltq_etop_chan *ch = &priv->ch[i];

		if (!IS_TX(i) && (!IS_RX(i)))
			continue;
		ltq_dma_open(&ch->dma);
		ltq_dma_enable_irq(&ch->dma);
		napi_enable(&ch->napi);
	}
	phy_start(dev->phydev);
	netif_tx_start_all_queues(dev);
	return 0;
}