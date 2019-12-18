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
struct net_device {int dummy; } ;
struct mlx5e_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int cmd; TYPE_1__ fs; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXCLSRLDEL 130 
#define  ETHTOOL_SRXCLSRLINS 129 
#define  ETHTOOL_SRXFH 128 
 int mlx5e_ethtool_flow_remove (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int mlx5e_ethtool_flow_replace (struct mlx5e_priv*,TYPE_1__*) ; 
 int mlx5e_set_rss_hash_opt (struct mlx5e_priv*,struct ethtool_rxnfc*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

int mlx5e_ethtool_set_rxnfc(struct net_device *dev, struct ethtool_rxnfc *cmd)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	int err = 0;

	switch (cmd->cmd) {
	case ETHTOOL_SRXCLSRLINS:
		err = mlx5e_ethtool_flow_replace(priv, &cmd->fs);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		err = mlx5e_ethtool_flow_remove(priv, cmd->fs.location);
		break;
	case ETHTOOL_SRXFH:
		err = mlx5e_set_rss_hash_opt(priv, cmd);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}