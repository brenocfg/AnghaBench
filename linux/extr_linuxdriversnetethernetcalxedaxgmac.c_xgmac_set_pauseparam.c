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
struct xgmac_priv {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 int EINVAL ; 
 struct xgmac_priv* netdev_priv (struct net_device*) ; 
 int xgmac_set_flow_ctrl (struct xgmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgmac_set_pauseparam(struct net_device *netdev,
				     struct ethtool_pauseparam *pause)
{
	struct xgmac_priv *priv = netdev_priv(netdev);

	if (pause->autoneg)
		return -EINVAL;

	return xgmac_set_flow_ctrl(priv, pause->rx_pause, pause->tx_pause);
}