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
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;
struct ieee_ets {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,struct ieee_ets*) ; 
 int mlx5e_dbcnl_validate_ets (struct net_device*,struct ieee_ets*,int) ; 
 int mlx5e_dcbnl_ieee_setets_core (struct mlx5e_priv*,struct ieee_ets*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_dcbnl_ieee_setets(struct net_device *netdev,
				   struct ieee_ets *ets)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	int err;

	if (!MLX5_CAP_GEN(priv->mdev, ets))
		return -EOPNOTSUPP;

	err = mlx5e_dbcnl_validate_ets(netdev, ets, false);
	if (err)
		return err;

	err = mlx5e_dcbnl_ieee_setets_core(priv, ets);
	if (err)
		return err;

	return 0;
}