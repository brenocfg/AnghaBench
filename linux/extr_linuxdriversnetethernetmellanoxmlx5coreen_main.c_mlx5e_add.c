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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,...) ; 
 int mlx5e_attach (struct mlx5_core_dev*,void*) ; 
 int mlx5e_check_required_hca_cap (struct mlx5_core_dev*) ; 
 struct net_device* mlx5e_create_netdev (struct mlx5_core_dev*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  mlx5e_destroy_netdev (void*) ; 
 int /*<<< orphan*/  mlx5e_detach (struct mlx5_core_dev*,void*) ; 
 int /*<<< orphan*/  mlx5e_nic_profile ; 
 void* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static void *mlx5e_add(struct mlx5_core_dev *mdev)
{
	struct net_device *netdev;
	void *rpriv = NULL;
	void *priv;
	int err;

	err = mlx5e_check_required_hca_cap(mdev);
	if (err)
		return NULL;

#ifdef CONFIG_MLX5_ESWITCH
	if (MLX5_ESWITCH_MANAGER(mdev)) {
		rpriv = mlx5e_alloc_nic_rep_priv(mdev);
		if (!rpriv) {
			mlx5_core_warn(mdev, "Failed to alloc NIC rep priv data\n");
			return NULL;
		}
	}
#endif

	netdev = mlx5e_create_netdev(mdev, &mlx5e_nic_profile, rpriv);
	if (!netdev) {
		mlx5_core_err(mdev, "mlx5e_create_netdev failed\n");
		goto err_free_rpriv;
	}

	priv = netdev_priv(netdev);

	err = mlx5e_attach(mdev, priv);
	if (err) {
		mlx5_core_err(mdev, "mlx5e_attach failed, %d\n", err);
		goto err_destroy_netdev;
	}

	err = register_netdev(netdev);
	if (err) {
		mlx5_core_err(mdev, "register_netdev failed, %d\n", err);
		goto err_detach;
	}

#ifdef CONFIG_MLX5_CORE_EN_DCB
	mlx5e_dcbnl_init_app(priv);
#endif
	return priv;

err_detach:
	mlx5e_detach(mdev, priv);
err_destroy_netdev:
	mlx5e_destroy_netdev(priv);
err_free_rpriv:
	kfree(rpriv);
	return NULL;
}