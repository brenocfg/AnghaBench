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
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  autoneg; } ;
struct bcm_enet_priv {int /*<<< orphan*/  pause_tx; int /*<<< orphan*/  pause_rx; int /*<<< orphan*/  pause_auto; } ;

/* Variables and functions */
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bcm_enet_get_pauseparam(struct net_device *dev,
				    struct ethtool_pauseparam *ecmd)
{
	struct bcm_enet_priv *priv;

	priv = netdev_priv(dev);
	ecmd->autoneg = priv->pause_auto;
	ecmd->rx_pause = priv->pause_rx;
	ecmd->tx_pause = priv->pause_tx;
}