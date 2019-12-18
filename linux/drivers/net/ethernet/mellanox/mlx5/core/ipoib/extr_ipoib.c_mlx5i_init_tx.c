#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  qpn; } ;
struct mlx5i_priv {TYPE_1__ qp; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; int /*<<< orphan*/ ** tisn; struct mlx5i_priv* ppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int) ; 
 int mlx5i_create_tis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5i_create_underlay_qp (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5i_destroy_underlay_qp (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int mlx5i_init_tx(struct mlx5e_priv *priv)
{
	struct mlx5i_priv *ipriv = priv->ppriv;
	int err;

	err = mlx5i_create_underlay_qp(priv->mdev, &ipriv->qp);
	if (err) {
		mlx5_core_warn(priv->mdev, "create underlay QP failed, %d\n", err);
		return err;
	}

	err = mlx5i_create_tis(priv->mdev, ipriv->qp.qpn, &priv->tisn[0][0]);
	if (err) {
		mlx5_core_warn(priv->mdev, "create tis failed, %d\n", err);
		goto err_destroy_underlay_qp;
	}

	return 0;

err_destroy_underlay_qp:
	mlx5i_destroy_underlay_qp(priv->mdev, &ipriv->qp);
	return err;
}