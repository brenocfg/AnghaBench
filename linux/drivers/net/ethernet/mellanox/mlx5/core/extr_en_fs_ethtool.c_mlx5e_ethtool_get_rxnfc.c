#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tot_num_rules; } ;
struct TYPE_5__ {TYPE_1__ ethtool; } ;
struct mlx5e_priv {TYPE_2__ fs; } ;
struct TYPE_6__ {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int cmd; TYPE_3__ fs; int /*<<< orphan*/  rule_cnt; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 131 
#define  ETHTOOL_GRXCLSRLCNT 130 
#define  ETHTOOL_GRXCLSRULE 129 
#define  ETHTOOL_GRXFH 128 
 int mlx5e_ethtool_get_all_flows (struct mlx5e_priv*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 int mlx5e_ethtool_get_flow (struct mlx5e_priv*,struct ethtool_rxnfc*,int /*<<< orphan*/ ) ; 
 int mlx5e_get_rss_hash_opt (struct mlx5e_priv*,struct ethtool_rxnfc*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

int mlx5e_ethtool_get_rxnfc(struct net_device *dev,
			    struct ethtool_rxnfc *info, u32 *rule_locs)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	int err = 0;

	switch (info->cmd) {
	case ETHTOOL_GRXCLSRLCNT:
		info->rule_cnt = priv->fs.ethtool.tot_num_rules;
		break;
	case ETHTOOL_GRXCLSRULE:
		err = mlx5e_ethtool_get_flow(priv, info, info->fs.location);
		break;
	case ETHTOOL_GRXCLSRLALL:
		err = mlx5e_ethtool_get_all_flows(priv, info, rule_locs);
		break;
	case ETHTOOL_GRXFH:
		err =  mlx5e_get_rss_hash_opt(priv, info);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}