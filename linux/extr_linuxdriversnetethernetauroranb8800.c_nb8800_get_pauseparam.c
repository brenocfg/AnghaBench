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
struct nb8800_priv {int /*<<< orphan*/  pause_tx; int /*<<< orphan*/  pause_rx; int /*<<< orphan*/  pause_aneg; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 struct nb8800_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nb8800_get_pauseparam(struct net_device *dev,
				  struct ethtool_pauseparam *pp)
{
	struct nb8800_priv *priv = netdev_priv(dev);

	pp->autoneg = priv->pause_aneg;
	pp->rx_pause = priv->pause_rx;
	pp->tx_pause = priv->pause_tx;
}