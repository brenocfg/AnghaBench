#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  mtu; } ;
struct mlx5e_rss_params {int dummy; } ;
struct mlx5e_profile {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  params; } ;
struct mlx5e_priv {int /*<<< orphan*/  max_nch; TYPE_1__ channels; int /*<<< orphan*/  xsk; struct mlx5e_rss_params rss_params; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5e_build_nic_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mlx5e_build_nic_params (struct mlx5_core_dev*,int /*<<< orphan*/ *,struct mlx5e_rss_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_build_tc2txq_maps (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_health_create_reporters (struct mlx5e_priv*) ; 
 int mlx5e_ipsec_init (struct mlx5e_priv*) ; 
 int mlx5e_netdev_init (struct net_device*,struct mlx5e_priv*,struct mlx5_core_dev*,struct mlx5e_profile const*,void*) ; 
 int /*<<< orphan*/  mlx5e_timestamp_init (struct mlx5e_priv*) ; 
 int mlx5e_tls_init (struct mlx5e_priv*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_nic_init(struct mlx5_core_dev *mdev,
			  struct net_device *netdev,
			  const struct mlx5e_profile *profile,
			  void *ppriv)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_rss_params *rss = &priv->rss_params;
	int err;

	err = mlx5e_netdev_init(netdev, priv, mdev, profile, ppriv);
	if (err)
		return err;

	mlx5e_build_nic_params(mdev, &priv->xsk, rss, &priv->channels.params,
			       priv->max_nch, netdev->mtu);

	mlx5e_timestamp_init(priv);

	err = mlx5e_ipsec_init(priv);
	if (err)
		mlx5_core_err(mdev, "IPSec initialization failed, %d\n", err);
	err = mlx5e_tls_init(priv);
	if (err)
		mlx5_core_err(mdev, "TLS initialization failed, %d\n", err);
	mlx5e_build_nic_netdev(netdev);
	mlx5e_build_tc2txq_maps(priv);
	mlx5e_health_create_reporters(priv);

	return 0;
}