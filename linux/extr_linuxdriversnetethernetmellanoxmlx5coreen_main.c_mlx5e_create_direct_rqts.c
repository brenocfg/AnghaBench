#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_rqt {int dummy; } ;
struct mlx5e_priv {TYPE_1__* direct_tir; int /*<<< orphan*/  mdev; TYPE_2__* profile; } ;
struct TYPE_4__ {int (* max_nch ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct mlx5e_rqt rqt; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int) ; 
 int mlx5e_create_rqt (struct mlx5e_priv*,int,struct mlx5e_rqt*) ; 
 int /*<<< orphan*/  mlx5e_destroy_rqt (struct mlx5e_priv*,struct mlx5e_rqt*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int mlx5e_create_direct_rqts(struct mlx5e_priv *priv)
{
	struct mlx5e_rqt *rqt;
	int err;
	int ix;

	for (ix = 0; ix < priv->profile->max_nch(priv->mdev); ix++) {
		rqt = &priv->direct_tir[ix].rqt;
		err = mlx5e_create_rqt(priv, 1 /*size */, rqt);
		if (err)
			goto err_destroy_rqts;
	}

	return 0;

err_destroy_rqts:
	mlx5_core_warn(priv->mdev, "create direct rqts failed, %d\n", err);
	for (ix--; ix >= 0; ix--)
		mlx5e_destroy_rqt(priv, &priv->direct_tir[ix].rqt);

	return err;
}