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
struct TYPE_3__ {int /*<<< orphan*/  active_svlans; } ;
struct TYPE_4__ {TYPE_1__ vlan; } ;
struct mlx5e_priv {TYPE_2__ fs; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5e_add_vlan_rule (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_vlan_rx_add_svid(struct mlx5e_priv *priv, u16 vid)
{
	struct net_device *netdev = priv->netdev;
	int err;

	set_bit(vid, priv->fs.vlan.active_svlans);

	err = mlx5e_add_vlan_rule(priv, MLX5E_VLAN_RULE_TYPE_MATCH_STAG_VID, vid);
	if (err) {
		clear_bit(vid, priv->fs.vlan.active_svlans);
		return err;
	}

	/* Need to fix some features.. */
	netdev_update_features(netdev);
	return err;
}