#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int /*<<< orphan*/  autoneg; } ;
struct TYPE_2__ {int options; } ;
struct dpaa2_eth_priv {TYPE_1__ link_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int DPNI_LINK_OPT_ASYM_PAUSE ; 
 int DPNI_LINK_OPT_PAUSE ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void dpaa2_eth_get_pauseparam(struct net_device *net_dev,
				     struct ethtool_pauseparam *pause)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	u64 link_options = priv->link_state.options;

	pause->rx_pause = !!(link_options & DPNI_LINK_OPT_PAUSE);
	pause->tx_pause = pause->rx_pause ^
			  !!(link_options & DPNI_LINK_OPT_ASYM_PAUSE);
	pause->autoneg = AUTONEG_DISABLE;
}