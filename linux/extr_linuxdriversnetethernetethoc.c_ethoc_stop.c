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
struct net_device {int /*<<< orphan*/  irq; scalar_t__ phydev; } ;
struct ethoc {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ethoc_disable_rx_and_tx (struct ethoc*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 

__attribute__((used)) static int ethoc_stop(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);

	napi_disable(&priv->napi);

	if (dev->phydev)
		phy_stop(dev->phydev);

	ethoc_disable_rx_and_tx(priv);
	free_irq(dev->irq, dev);

	if (!netif_queue_stopped(dev))
		netif_stop_queue(dev);

	return 0;
}