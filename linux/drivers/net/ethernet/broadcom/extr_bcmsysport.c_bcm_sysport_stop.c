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
struct net_device {unsigned int num_tx_queues; int /*<<< orphan*/  phydev; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  irq1; int /*<<< orphan*/  is_lite; int /*<<< orphan*/  irq0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RX_EN ; 
 int /*<<< orphan*/  CMD_TX_EN ; 
 int /*<<< orphan*/  bcm_sysport_fini_rx_ring (struct bcm_sysport_priv*) ; 
 int /*<<< orphan*/  bcm_sysport_fini_tx_ring (struct bcm_sysport_priv*,unsigned int) ; 
 int /*<<< orphan*/  bcm_sysport_netif_stop (struct net_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int rdma_enable_set (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int tdma_enable_set (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_enable_set (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bcm_sysport_stop(struct net_device *dev)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	unsigned int i;
	int ret;

	bcm_sysport_netif_stop(dev);

	/* Disable UniMAC RX */
	umac_enable_set(priv, CMD_RX_EN, 0);

	ret = tdma_enable_set(priv, 0);
	if (ret) {
		netdev_err(dev, "timeout disabling RDMA\n");
		return ret;
	}

	/* Wait for a maximum packet size to be drained */
	usleep_range(2000, 3000);

	ret = rdma_enable_set(priv, 0);
	if (ret) {
		netdev_err(dev, "timeout disabling TDMA\n");
		return ret;
	}

	/* Disable UniMAC TX */
	umac_enable_set(priv, CMD_TX_EN, 0);

	/* Free RX/TX rings SW structures */
	for (i = 0; i < dev->num_tx_queues; i++)
		bcm_sysport_fini_tx_ring(priv, i);
	bcm_sysport_fini_rx_ring(priv);

	free_irq(priv->irq0, dev);
	if (!priv->is_lite)
		free_irq(priv->irq1, dev);

	/* Disconnect from PHY */
	phy_disconnect(dev->phydev);

	return 0;
}