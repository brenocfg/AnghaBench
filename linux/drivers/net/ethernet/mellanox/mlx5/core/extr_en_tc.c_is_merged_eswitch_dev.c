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
struct mlx5e_priv {struct net_device* netdev; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_ESW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merged_eswitch ; 
 scalar_t__ mlx5e_eswitch_rep (struct net_device*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ same_hw_devs (struct mlx5e_priv*,struct mlx5e_priv*) ; 

__attribute__((used)) static bool is_merged_eswitch_dev(struct mlx5e_priv *priv,
				  struct net_device *peer_netdev)
{
	struct mlx5e_priv *peer_priv;

	peer_priv = netdev_priv(peer_netdev);

	return (MLX5_CAP_ESW(priv->mdev, merged_eswitch) &&
		mlx5e_eswitch_rep(priv->netdev) &&
		mlx5e_eswitch_rep(peer_netdev) &&
		same_hw_devs(priv, peer_priv));
}