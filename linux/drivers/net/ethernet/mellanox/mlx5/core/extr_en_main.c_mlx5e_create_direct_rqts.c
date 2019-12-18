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
struct mlx5e_tir {int /*<<< orphan*/  rqt; } ;
struct mlx5e_priv {int max_nch; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int) ; 
 int mlx5e_create_rqt (struct mlx5e_priv*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_rqt (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int mlx5e_create_direct_rqts(struct mlx5e_priv *priv, struct mlx5e_tir *tirs)
{
	int err;
	int ix;

	for (ix = 0; ix < priv->max_nch; ix++) {
		err = mlx5e_create_rqt(priv, 1 /*size */, &tirs[ix].rqt);
		if (unlikely(err))
			goto err_destroy_rqts;
	}

	return 0;

err_destroy_rqts:
	mlx5_core_warn(priv->mdev, "create rqts failed, %d\n", err);
	for (ix--; ix >= 0; ix--)
		mlx5e_destroy_rqt(priv, &tirs[ix].rqt);

	return err;
}