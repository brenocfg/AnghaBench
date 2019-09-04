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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  rqtn; } ;
struct mlx5e_tir {TYPE_2__ rqt; } ;
struct mlx5e_priv {struct mlx5e_tir* direct_tir; int /*<<< orphan*/  mdev; TYPE_1__* profile; } ;
struct TYPE_3__ {int (* max_nch ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tir_in ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mlx5e_build_direct_tir_ctx (struct mlx5e_priv*,int /*<<< orphan*/ ,void*) ; 
 int mlx5e_create_tir (int /*<<< orphan*/ ,struct mlx5e_tir*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5e_destroy_tir (int /*<<< orphan*/ ,struct mlx5e_tir*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int mlx5e_create_direct_tirs(struct mlx5e_priv *priv)
{
	int nch = priv->profile->max_nch(priv->mdev);
	struct mlx5e_tir *tir;
	void *tirc;
	int inlen;
	int err;
	u32 *in;
	int ix;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	for (ix = 0; ix < nch; ix++) {
		memset(in, 0, inlen);
		tir = &priv->direct_tir[ix];
		tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);
		mlx5e_build_direct_tir_ctx(priv, priv->direct_tir[ix].rqt.rqtn, tirc);
		err = mlx5e_create_tir(priv->mdev, tir, in, inlen);
		if (err)
			goto err_destroy_ch_tirs;
	}

	kvfree(in);

	return 0;

err_destroy_ch_tirs:
	mlx5_core_warn(priv->mdev, "create direct tirs failed, %d\n", err);
	for (ix--; ix >= 0; ix--)
		mlx5e_destroy_tir(priv->mdev, &priv->direct_tir[ix]);

	kvfree(in);

	return err;
}