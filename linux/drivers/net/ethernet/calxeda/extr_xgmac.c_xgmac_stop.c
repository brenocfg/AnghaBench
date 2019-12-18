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
struct xgmac_priv {scalar_t__ base; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ XGMAC_DMA_INTR_ENA ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct xgmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xgmac_free_dma_desc_rings (struct xgmac_priv*) ; 
 int /*<<< orphan*/  xgmac_mac_disable (scalar_t__) ; 

__attribute__((used)) static int xgmac_stop(struct net_device *dev)
{
	struct xgmac_priv *priv = netdev_priv(dev);

	if (readl(priv->base + XGMAC_DMA_INTR_ENA))
		napi_disable(&priv->napi);

	writel(0, priv->base + XGMAC_DMA_INTR_ENA);

	netif_tx_disable(dev);

	/* Disable the MAC core */
	xgmac_mac_disable(priv->base);

	/* Release and free the Rx/Tx resources */
	xgmac_free_dma_desc_rings(priv);

	return 0;
}