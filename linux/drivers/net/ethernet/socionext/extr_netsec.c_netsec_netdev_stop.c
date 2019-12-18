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
struct netsec_priv {int /*<<< orphan*/  dev; TYPE_1__* ndev; int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETSEC_REG_INTEN_CLR ; 
 int /*<<< orphan*/  NETSEC_RING_RX ; 
 int /*<<< orphan*/  NETSEC_RING_TX ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct netsec_priv*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct netsec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_1__*) ; 
 int netsec_reset_hardware (struct netsec_priv*,int) ; 
 int /*<<< orphan*/  netsec_stop_gmac (struct netsec_priv*) ; 
 int /*<<< orphan*/  netsec_uninit_pkt_dring (struct netsec_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netsec_write (struct netsec_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netsec_netdev_stop(struct net_device *ndev)
{
	int ret;
	struct netsec_priv *priv = netdev_priv(ndev);

	netif_stop_queue(priv->ndev);
	dma_wmb();

	napi_disable(&priv->napi);

	netsec_write(priv, NETSEC_REG_INTEN_CLR, ~0);
	netsec_stop_gmac(priv);

	free_irq(priv->ndev->irq, priv);

	netsec_uninit_pkt_dring(priv, NETSEC_RING_TX);
	netsec_uninit_pkt_dring(priv, NETSEC_RING_RX);

	phy_stop(ndev->phydev);
	phy_disconnect(ndev->phydev);

	ret = netsec_reset_hardware(priv, false);

	pm_runtime_put_sync(priv->dev);

	return ret;
}