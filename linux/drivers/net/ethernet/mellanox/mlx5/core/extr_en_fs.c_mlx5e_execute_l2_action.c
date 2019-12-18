#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; int /*<<< orphan*/  mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct mlx5e_l2_hash_node {int action; int mpfs; TYPE_1__ ai; } ;

/* Variables and functions */
 int ETH_ALEN ; 
#define  MLX5E_ACTION_ADD 129 
#define  MLX5E_ACTION_DEL 128 
 int MLX5E_ACTION_NONE ; 
 int /*<<< orphan*/  MLX5E_FULLMATCH ; 
 int /*<<< orphan*/  ether_addr_copy (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int*) ; 
 int mlx5_mpfs_add_mac (int /*<<< orphan*/ ,int*) ; 
 int mlx5_mpfs_del_mac (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mlx5e_add_l2_flow_rule (struct mlx5e_priv*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_del_l2_flow_rule (struct mlx5e_priv*,TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5e_del_l2_from_hash (struct mlx5e_l2_hash_node*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,char*,int*,int) ; 

__attribute__((used)) static void mlx5e_execute_l2_action(struct mlx5e_priv *priv,
				    struct mlx5e_l2_hash_node *hn)
{
	u8 action = hn->action;
	u8 mac_addr[ETH_ALEN];
	int l2_err = 0;

	ether_addr_copy(mac_addr, hn->ai.addr);

	switch (action) {
	case MLX5E_ACTION_ADD:
		mlx5e_add_l2_flow_rule(priv, &hn->ai, MLX5E_FULLMATCH);
		if (!is_multicast_ether_addr(mac_addr)) {
			l2_err = mlx5_mpfs_add_mac(priv->mdev, mac_addr);
			hn->mpfs = !l2_err;
		}
		hn->action = MLX5E_ACTION_NONE;
		break;

	case MLX5E_ACTION_DEL:
		if (!is_multicast_ether_addr(mac_addr) && hn->mpfs)
			l2_err = mlx5_mpfs_del_mac(priv->mdev, mac_addr);
		mlx5e_del_l2_flow_rule(priv, &hn->ai);
		mlx5e_del_l2_from_hash(hn);
		break;
	}

	if (l2_err)
		netdev_warn(priv->netdev, "MPFS, failed to %s mac %pM, err(%d)\n",
			    action == MLX5E_ACTION_ADD ? "add" : "del", mac_addr, l2_err);
}