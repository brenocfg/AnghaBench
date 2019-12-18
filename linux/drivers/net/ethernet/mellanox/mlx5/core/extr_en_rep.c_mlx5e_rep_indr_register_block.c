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
struct mlx5e_rep_priv {int /*<<< orphan*/  netdev; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int __flow_indr_block_cb_register (struct net_device*,struct mlx5e_rep_priv*,int /*<<< orphan*/ ,struct mlx5e_rep_priv*) ; 
 int /*<<< orphan*/  mlx5_core_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5e_rep_indr_setup_tc_cb ; 
 int /*<<< orphan*/  netdev_name (struct net_device*) ; 
 struct mlx5e_priv* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_rep_indr_register_block(struct mlx5e_rep_priv *rpriv,
					 struct net_device *netdev)
{
	int err;

	err = __flow_indr_block_cb_register(netdev, rpriv,
					    mlx5e_rep_indr_setup_tc_cb,
					    rpriv);
	if (err) {
		struct mlx5e_priv *priv = netdev_priv(rpriv->netdev);

		mlx5_core_err(priv->mdev, "Failed to register remote block notifier for %s err=%d\n",
			      netdev_name(netdev), err);
	}
	return err;
}