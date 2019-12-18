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
struct mlx5i_priv {int /*<<< orphan*/  sub_interface; } ;
struct mlx5e_profile {int /*<<< orphan*/  (* cleanup ) (struct mlx5e_priv*) ;} ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct mlx5e_profile* profile; struct mlx5i_priv* ppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_destroy_mdev_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_detach_netdev (struct mlx5e_priv*) ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_pkey_qpn_ht_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 

__attribute__((used)) static void mlx5_rdma_netdev_free(struct net_device *netdev)
{
	struct mlx5e_priv *priv = mlx5i_epriv(netdev);
	struct mlx5i_priv *ipriv = priv->ppriv;
	const struct mlx5e_profile *profile = priv->profile;

	mlx5e_detach_netdev(priv);
	profile->cleanup(priv);

	if (!ipriv->sub_interface) {
		mlx5i_pkey_qpn_ht_cleanup(netdev);
		mlx5e_destroy_mdev_resources(priv->mdev);
	}
}