#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_svlans; int /*<<< orphan*/  active_cvlans; } ;
struct TYPE_4__ {TYPE_1__ vlan; } ;
struct mlx5e_priv {TYPE_2__ fs; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ ETH_P_8021AD ; 
 scalar_t__ ETH_P_8021Q ; 
 int /*<<< orphan*/  MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID ; 
 int /*<<< orphan*/  MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_del_vlan_rule (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 

int mlx5e_vlan_rx_kill_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	if (be16_to_cpu(proto) == ETH_P_8021Q) {
		clear_bit(vid, priv->fs.vlan.active_cvlans);
		mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_CTAG_VID, vid);
	} else if (be16_to_cpu(proto) == ETH_P_8021AD) {
		clear_bit(vid, priv->fs.vlan.active_svlans);
		mlx5e_del_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID, vid);
		netdev_update_features(dev);
	}

	return 0;
}