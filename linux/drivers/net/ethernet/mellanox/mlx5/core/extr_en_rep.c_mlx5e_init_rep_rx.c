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
struct TYPE_2__ {int /*<<< orphan*/  ttc; } ;
struct mlx5e_priv {int /*<<< orphan*/  drop_rq; int /*<<< orphan*/  indir_rqt; int /*<<< orphan*/  direct_tir; TYPE_1__ fs; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5e_close_drop_rq (int /*<<< orphan*/ *) ; 
 int mlx5e_create_direct_rqts (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int mlx5e_create_direct_tirs (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int mlx5e_create_indirect_rqt (struct mlx5e_priv*) ; 
 int mlx5e_create_indirect_tirs (struct mlx5e_priv*,int) ; 
 int mlx5e_create_rep_ttc_table (struct mlx5e_priv*) ; 
 int mlx5e_create_rep_vport_rx_rule (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_rqts (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_tirs (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_indirect_tirs (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  mlx5e_destroy_rqt (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_ttc_table (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_init_l2_addr (struct mlx5e_priv*) ; 
 int mlx5e_open_drop_rq (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_init_rep_rx(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int err;

	mlx5e_init_l2_addr(priv);

	err = mlx5e_open_drop_rq(priv, &priv->drop_rq);
	if (err) {
		mlx5_core_err(mdev, "open drop rq failed, %d\n", err);
		return err;
	}

	err = mlx5e_create_indirect_rqt(priv);
	if (err)
		goto err_close_drop_rq;

	err = mlx5e_create_direct_rqts(priv, priv->direct_tir);
	if (err)
		goto err_destroy_indirect_rqts;

	err = mlx5e_create_indirect_tirs(priv, false);
	if (err)
		goto err_destroy_direct_rqts;

	err = mlx5e_create_direct_tirs(priv, priv->direct_tir);
	if (err)
		goto err_destroy_indirect_tirs;

	err = mlx5e_create_rep_ttc_table(priv);
	if (err)
		goto err_destroy_direct_tirs;

	err = mlx5e_create_rep_vport_rx_rule(priv);
	if (err)
		goto err_destroy_ttc_table;

	return 0;

err_destroy_ttc_table:
	mlx5e_destroy_ttc_table(priv, &priv->fs.ttc);
err_destroy_direct_tirs:
	mlx5e_destroy_direct_tirs(priv, priv->direct_tir);
err_destroy_indirect_tirs:
	mlx5e_destroy_indirect_tirs(priv, false);
err_destroy_direct_rqts:
	mlx5e_destroy_direct_rqts(priv, priv->direct_tir);
err_destroy_indirect_rqts:
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
err_close_drop_rq:
	mlx5e_close_drop_rq(&priv->drop_rq);
	return err;
}