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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; } ;
typedef  enum mlx5e_priv_flag { ____Placeholder_mlx5e_priv_flag } mlx5e_priv_flag ;

/* Variables and functions */
 int MLX5E_NUM_PFLAGS ; 
 int mlx5e_handle_pflag (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 

__attribute__((used)) static int mlx5e_set_priv_flags(struct net_device *netdev, u32 pflags)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	enum mlx5e_priv_flag pflag;
	int err;

	mutex_lock(&priv->state_lock);

	for (pflag = 0; pflag < MLX5E_NUM_PFLAGS; pflag++) {
		err = mlx5e_handle_pflag(netdev, pflags, pflag);
		if (err)
			break;
	}

	mutex_unlock(&priv->state_lock);

	/* Need to fix some features.. */
	netdev_update_features(netdev);

	return err;
}