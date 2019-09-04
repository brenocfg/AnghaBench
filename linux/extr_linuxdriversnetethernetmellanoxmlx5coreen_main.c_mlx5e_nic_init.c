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
struct mlx5e_profile {int dummy; } ;
struct mlx5e_priv {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5e_build_nic_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mlx5e_build_nic_netdev_priv (struct mlx5_core_dev*,struct net_device*,struct mlx5e_profile const*,void*) ; 
 int /*<<< orphan*/  mlx5e_build_tc2txq_maps (struct mlx5e_priv*) ; 
 int mlx5e_ipsec_init (struct mlx5e_priv*) ; 
 int mlx5e_tls_init (struct mlx5e_priv*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx5e_nic_init(struct mlx5_core_dev *mdev,
			   struct net_device *netdev,
			   const struct mlx5e_profile *profile,
			   void *ppriv)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	int err;

	mlx5e_build_nic_netdev_priv(mdev, netdev, profile, ppriv);
	err = mlx5e_ipsec_init(priv);
	if (err)
		mlx5_core_err(mdev, "IPSec initialization failed, %d\n", err);
	err = mlx5e_tls_init(priv);
	if (err)
		mlx5_core_err(mdev, "TLS initialization failed, %d\n", err);
	mlx5e_build_nic_netdev(netdev);
	mlx5e_build_tc2txq_maps(priv);
}