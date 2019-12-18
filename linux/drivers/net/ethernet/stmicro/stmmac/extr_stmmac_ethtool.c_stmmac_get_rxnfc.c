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
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {TYPE_1__* plat; } ;
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_queues_to_use; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXRINGS 128 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int stmmac_get_rxnfc(struct net_device *dev,
			    struct ethtool_rxnfc *rxnfc, u32 *rule_locs)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	switch (rxnfc->cmd) {
	case ETHTOOL_GRXRINGS:
		rxnfc->data = priv->plat->rx_queues_to_use;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}