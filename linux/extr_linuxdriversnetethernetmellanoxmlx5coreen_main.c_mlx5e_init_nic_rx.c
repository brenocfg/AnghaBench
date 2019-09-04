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
struct mlx5e_priv {int /*<<< orphan*/  indir_rqt; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5e_create_direct_rqts (struct mlx5e_priv*) ; 
 int mlx5e_create_direct_tirs (struct mlx5e_priv*) ; 
 int mlx5e_create_flow_steering (struct mlx5e_priv*) ; 
 int mlx5e_create_indirect_rqt (struct mlx5e_priv*) ; 
 int mlx5e_create_indirect_tirs (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_rqts (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_tirs (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_flow_steering (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_indirect_tirs (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_rqt (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int mlx5e_tc_nic_init (struct mlx5e_priv*) ; 

__attribute__((used)) static int mlx5e_init_nic_rx(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int err;

	err = mlx5e_create_indirect_rqt(priv);
	if (err)
		return err;

	err = mlx5e_create_direct_rqts(priv);
	if (err)
		goto err_destroy_indirect_rqts;

	err = mlx5e_create_indirect_tirs(priv);
	if (err)
		goto err_destroy_direct_rqts;

	err = mlx5e_create_direct_tirs(priv);
	if (err)
		goto err_destroy_indirect_tirs;

	err = mlx5e_create_flow_steering(priv);
	if (err) {
		mlx5_core_warn(mdev, "create flow steering failed, %d\n", err);
		goto err_destroy_direct_tirs;
	}

	err = mlx5e_tc_nic_init(priv);
	if (err)
		goto err_destroy_flow_steering;

	return 0;

err_destroy_flow_steering:
	mlx5e_destroy_flow_steering(priv);
err_destroy_direct_tirs:
	mlx5e_destroy_direct_tirs(priv);
err_destroy_indirect_tirs:
	mlx5e_destroy_indirect_tirs(priv);
err_destroy_direct_rqts:
	mlx5e_destroy_direct_rqts(priv);
err_destroy_indirect_rqts:
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
	return err;
}