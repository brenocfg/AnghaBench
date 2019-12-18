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
struct ave_private {int /*<<< orphan*/  pause_tx; int /*<<< orphan*/  pause_rx; int /*<<< orphan*/  pause_auto; } ;

/* Variables and functions */
 struct ave_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ave_ethtool_get_pauseparam(struct net_device *ndev,
				       struct ethtool_pauseparam *pause)
{
	struct ave_private *priv = netdev_priv(ndev);

	pause->autoneg  = priv->pause_auto;
	pause->rx_pause = priv->pause_rx;
	pause->tx_pause = priv->pause_tx;
}