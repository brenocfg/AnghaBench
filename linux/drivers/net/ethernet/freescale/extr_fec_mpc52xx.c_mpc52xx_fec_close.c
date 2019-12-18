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
struct mpc52xx_fec_priv {int /*<<< orphan*/  t_irq; int /*<<< orphan*/  r_irq; int /*<<< orphan*/  rx_dmatsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mpc52xx_fec_free_rx_buffers (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc52xx_fec_stop (struct net_device*) ; 
 struct mpc52xx_fec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_stop (struct phy_device*) ; 

__attribute__((used)) static int mpc52xx_fec_close(struct net_device *dev)
{
	struct mpc52xx_fec_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;

	netif_stop_queue(dev);

	mpc52xx_fec_stop(dev);

	mpc52xx_fec_free_rx_buffers(dev, priv->rx_dmatsk);

	free_irq(dev->irq, dev);
	free_irq(priv->r_irq, dev);
	free_irq(priv->t_irq, dev);

	if (phydev) {
		/* power down phy */
		phy_stop(phydev);
		phy_disconnect(phydev);
	}

	return 0;
}