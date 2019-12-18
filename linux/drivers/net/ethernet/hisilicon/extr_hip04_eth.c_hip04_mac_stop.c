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
struct net_device {int dummy; } ;
struct hip04_priv {scalar_t__* rx_phys; int /*<<< orphan*/  dev; scalar_t__ phy; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int RX_DESC_NUM ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hip04_mac_disable (struct net_device*) ; 
 int /*<<< orphan*/  hip04_reset_ppe (struct hip04_priv*) ; 
 int /*<<< orphan*/  hip04_tx_reclaim (struct net_device*,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 

__attribute__((used)) static int hip04_mac_stop(struct net_device *ndev)
{
	struct hip04_priv *priv = netdev_priv(ndev);
	int i;

	napi_disable(&priv->napi);
	netif_stop_queue(ndev);
	hip04_mac_disable(ndev);
	hip04_tx_reclaim(ndev, true);
	hip04_reset_ppe(priv);

	if (priv->phy)
		phy_stop(priv->phy);

	for (i = 0; i < RX_DESC_NUM; i++) {
		if (priv->rx_phys[i]) {
			dma_unmap_single(priv->dev, priv->rx_phys[i],
					 RX_BUF_SIZE, DMA_FROM_DEVICE);
			priv->rx_phys[i] = 0;
		}
	}

	return 0;
}