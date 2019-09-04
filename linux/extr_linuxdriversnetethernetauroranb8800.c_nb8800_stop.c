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
struct phy_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; struct phy_device* phydev; } ;
struct nb8800_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nb8800_dma_free (struct net_device*) ; 
 int /*<<< orphan*/  nb8800_dma_stop (struct net_device*) ; 
 int /*<<< orphan*/  nb8800_mac_rx (struct net_device*,int) ; 
 int /*<<< orphan*/  nb8800_mac_tx (struct net_device*,int) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_stop (struct phy_device*) ; 

__attribute__((used)) static int nb8800_stop(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;

	phy_stop(phydev);

	netif_stop_queue(dev);
	napi_disable(&priv->napi);

	nb8800_dma_stop(dev);
	nb8800_mac_rx(dev, false);
	nb8800_mac_tx(dev, false);

	phy_disconnect(phydev);

	free_irq(dev->irq, dev);

	nb8800_dma_free(dev);

	return 0;
}