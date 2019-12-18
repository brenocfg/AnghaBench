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
struct sxgbe_priv_data {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXFH 128 
 struct sxgbe_priv_data* netdev_priv (struct net_device*) ; 
 int sxgbe_set_rss_hash_opt (struct sxgbe_priv_data*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int sxgbe_set_rxnfc(struct net_device *dev, struct ethtool_rxnfc *cmd)
{
	struct sxgbe_priv_data *priv = netdev_priv(dev);
	int ret = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_SRXFH:
		ret = sxgbe_set_rss_hash_opt(priv, cmd);
		break;
	default:
		break;
	}

	return ret;
}