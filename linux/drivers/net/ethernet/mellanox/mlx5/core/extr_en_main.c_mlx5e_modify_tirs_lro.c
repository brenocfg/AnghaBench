#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  params; } ;
struct mlx5e_priv {int max_nch; TYPE_3__* direct_tir; TYPE_2__* indir_tir; TYPE_1__ channels; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lro; } ;
struct TYPE_7__ {int /*<<< orphan*/  tirn; } ;
struct TYPE_6__ {int /*<<< orphan*/  tirn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5E_NUM_INDIR_TIRS ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 TYPE_4__ bitmask ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_modify_tir (struct mlx5_core_dev*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  mlx5e_build_tir_ctx_lro (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  modify_tir_in ; 

__attribute__((used)) static int mlx5e_modify_tirs_lro(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;

	void *in;
	void *tirc;
	int inlen;
	int err;
	int tt;
	int ix;

	inlen = MLX5_ST_SZ_BYTES(modify_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	if (!in)
		return -ENOMEM;

	MLX5_SET(modify_tir_in, in, bitmask.lro, 1);
	tirc = MLX5_ADDR_OF(modify_tir_in, in, ctx);

	mlx5e_build_tir_ctx_lro(&priv->channels.params, tirc);

	for (tt = 0; tt < MLX5E_NUM_INDIR_TIRS; tt++) {
		err = mlx5_core_modify_tir(mdev, priv->indir_tir[tt].tirn, in,
					   inlen);
		if (err)
			goto free_in;
	}

	for (ix = 0; ix < priv->max_nch; ix++) {
		err = mlx5_core_modify_tir(mdev, priv->direct_tir[ix].tirn,
					   in, inlen);
		if (err)
			goto free_in;
	}

free_in:
	kvfree(in);

	return err;
}