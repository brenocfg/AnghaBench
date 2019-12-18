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
struct ethtool_pauseparam {int rx_pause; int tx_pause; int /*<<< orphan*/  autoneg; } ;
struct cpsw_priv {scalar_t__ tx_pause; scalar_t__ rx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 

void cpsw_get_pauseparam(struct net_device *ndev,
			 struct ethtool_pauseparam *pause)
{
	struct cpsw_priv *priv = netdev_priv(ndev);

	pause->autoneg = AUTONEG_DISABLE;
	pause->rx_pause = priv->rx_pause ? true : false;
	pause->tx_pause = priv->tx_pause ? true : false;
}