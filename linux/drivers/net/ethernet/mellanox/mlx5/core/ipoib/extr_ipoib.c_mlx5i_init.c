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
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  mtu; int /*<<< orphan*/  max_mtu; } ;
struct mlx5e_profile {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  params; } ;
struct mlx5e_priv {TYPE_1__ channels; int /*<<< orphan*/  max_nch; int /*<<< orphan*/  rss_params; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_GRO ; 
 int /*<<< orphan*/  NETIF_F_IPV6_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 int /*<<< orphan*/  NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  NETIF_F_RXHASH ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 int /*<<< orphan*/  NETIF_F_TSO ; 
 int /*<<< orphan*/  NETIF_F_TSO6 ; 
 int /*<<< orphan*/  mlx5e_build_nic_params (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5e_netdev_init (struct net_device*,struct mlx5e_priv*,struct mlx5_core_dev*,struct mlx5e_profile const*,void*) ; 
 int /*<<< orphan*/  mlx5e_set_netdev_mtu_boundaries (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_timestamp_init (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5i_build_nic_params (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_ethtool_ops ; 
 int /*<<< orphan*/  mlx5i_netdev_ops ; 

int mlx5i_init(struct mlx5_core_dev *mdev,
	       struct net_device *netdev,
	       const struct mlx5e_profile *profile,
	       void *ppriv)
{
	struct mlx5e_priv *priv  = mlx5i_epriv(netdev);
	int err;

	err = mlx5e_netdev_init(netdev, priv, mdev, profile, ppriv);
	if (err)
		return err;

	mlx5e_set_netdev_mtu_boundaries(priv);
	netdev->mtu = netdev->max_mtu;

	mlx5e_build_nic_params(mdev, NULL, &priv->rss_params, &priv->channels.params,
			       priv->max_nch, netdev->mtu);
	mlx5i_build_nic_params(mdev, &priv->channels.params);

	mlx5e_timestamp_init(priv);

	/* netdev init */
	netdev->hw_features    |= NETIF_F_SG;
	netdev->hw_features    |= NETIF_F_IP_CSUM;
	netdev->hw_features    |= NETIF_F_IPV6_CSUM;
	netdev->hw_features    |= NETIF_F_GRO;
	netdev->hw_features    |= NETIF_F_TSO;
	netdev->hw_features    |= NETIF_F_TSO6;
	netdev->hw_features    |= NETIF_F_RXCSUM;
	netdev->hw_features    |= NETIF_F_RXHASH;

	netdev->netdev_ops = &mlx5i_netdev_ops;
	netdev->ethtool_ops = &mlx5i_ethtool_ops;

	return 0;
}