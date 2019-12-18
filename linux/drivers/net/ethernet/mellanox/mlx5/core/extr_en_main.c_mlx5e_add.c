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
struct net_device {int dummy; } ;
typedef  void mlx5_core_dev ;
struct TYPE_2__ {int /*<<< orphan*/  eswitch; } ;

/* Variables and functions */
 scalar_t__ MLX5_ESWITCH_MANAGER (void*) ; 
 scalar_t__ MLX5_ESWITCH_OFFLOADS ; 
 int /*<<< orphan*/  mlx5_core_err (void*,char*,...) ; 
 scalar_t__ mlx5_eswitch_mode (int /*<<< orphan*/ ) ; 
 int mlx5e_attach (void*,void*) ; 
 int mlx5e_check_required_hca_cap (void*) ; 
 struct net_device* mlx5e_create_netdev (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_dcbnl_init_app (void*) ; 
 int /*<<< orphan*/  mlx5e_destroy_netdev (void*) ; 
 int /*<<< orphan*/  mlx5e_detach (void*,void*) ; 
 int mlx5e_get_max_num_channels (void*) ; 
 int /*<<< orphan*/  mlx5e_nic_profile ; 
 int /*<<< orphan*/  mlx5e_rep_register_vport_reps (void*) ; 
 void* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static void *mlx5e_add(struct mlx5_core_dev *mdev)
{
	struct net_device *netdev;
	void *priv;
	int err;
	int nch;

	err = mlx5e_check_required_hca_cap(mdev);
	if (err)
		return NULL;

#ifdef CONFIG_MLX5_ESWITCH
	if (MLX5_ESWITCH_MANAGER(mdev) &&
	    mlx5_eswitch_mode(mdev->priv.eswitch) == MLX5_ESWITCH_OFFLOADS) {
		mlx5e_rep_register_vport_reps(mdev);
		return mdev;
	}
#endif

	nch = mlx5e_get_max_num_channels(mdev);
	netdev = mlx5e_create_netdev(mdev, &mlx5e_nic_profile, nch, NULL);
	if (!netdev) {
		mlx5_core_err(mdev, "mlx5e_create_netdev failed\n");
		return NULL;
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
	return NULL;
}