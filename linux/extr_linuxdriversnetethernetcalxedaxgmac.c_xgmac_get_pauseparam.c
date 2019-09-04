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
struct xgmac_priv {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; } ;

/* Variables and functions */
 struct xgmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xgmac_get_pauseparam(struct net_device *netdev,
				      struct ethtool_pauseparam *pause)
{
	struct xgmac_priv *priv = netdev_priv(netdev);

	pause->rx_pause = priv->rx_pause;
	pause->tx_pause = priv->tx_pause;
}