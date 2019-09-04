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
struct mlx5e_profile {int (* max_nch ) (struct mlx5_core_dev*) ;int max_tc; int /*<<< orphan*/  (* cleanup ) (struct mlx5e_priv*) ;int /*<<< orphan*/  (* init ) (struct mlx5_core_dev*,struct net_device*,struct mlx5e_profile const*,void*) ;} ;
struct mlx5e_priv {int /*<<< orphan*/  wq; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 struct net_device* alloc_etherdev_mqs (int,int,int) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int stub1 (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  stub2 (struct mlx5_core_dev*,struct net_device*,struct mlx5e_profile const*,void*) ; 
 int /*<<< orphan*/  stub3 (struct mlx5e_priv*) ; 

struct net_device *mlx5e_create_netdev(struct mlx5_core_dev *mdev,
				       const struct mlx5e_profile *profile,
				       void *ppriv)
{
	int nch = profile->max_nch(mdev);
	struct net_device *netdev;
	struct mlx5e_priv *priv;

	netdev = alloc_etherdev_mqs(sizeof(struct mlx5e_priv),
				    nch * profile->max_tc,
				    nch);
	if (!netdev) {
		mlx5_core_err(mdev, "alloc_etherdev_mqs() failed\n");
		return NULL;
	}

#ifdef CONFIG_MLX5_EN_ARFS
	netdev->rx_cpu_rmap = mdev->rmap;
#endif

	profile->init(mdev, netdev, profile, ppriv);

	netif_carrier_off(netdev);

	priv = netdev_priv(netdev);

	priv->wq = create_singlethread_workqueue("mlx5e");
	if (!priv->wq)
		goto err_cleanup_nic;

	return netdev;

err_cleanup_nic:
	if (profile->cleanup)
		profile->cleanup(priv);
	free_netdev(netdev);

	return NULL;
}