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
struct ftgmac100 {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  aneg_pause; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 struct ftgmac100* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ftgmac100_get_pauseparam(struct net_device *netdev,
				     struct ethtool_pauseparam *pause)
{
	struct ftgmac100 *priv = netdev_priv(netdev);

	pause->autoneg = priv->aneg_pause;
	pause->tx_pause = priv->tx_pause;
	pause->rx_pause = priv->rx_pause;
}