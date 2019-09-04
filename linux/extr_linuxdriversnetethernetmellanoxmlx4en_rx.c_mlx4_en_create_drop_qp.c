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
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_en_priv {TYPE_1__* mdev; int /*<<< orphan*/  drop_qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_RESERVE_A0_QP ; 
 int /*<<< orphan*/  MLX4_RES_USAGE_DRIVER ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int mlx4_qp_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_qp_release_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlx4_qp_reserve_range (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_en_create_drop_qp(struct mlx4_en_priv *priv)
{
	int err;
	u32 qpn;

	err = mlx4_qp_reserve_range(priv->mdev->dev, 1, 1, &qpn,
				    MLX4_RESERVE_A0_QP,
				    MLX4_RES_USAGE_DRIVER);
	if (err) {
		en_err(priv, "Failed reserving drop qpn\n");
		return err;
	}
	err = mlx4_qp_alloc(priv->mdev->dev, qpn, &priv->drop_qp);
	if (err) {
		en_err(priv, "Failed allocating drop qp\n");
		mlx4_qp_release_range(priv->mdev->dev, qpn, 1);
		return err;
	}

	return 0;
}