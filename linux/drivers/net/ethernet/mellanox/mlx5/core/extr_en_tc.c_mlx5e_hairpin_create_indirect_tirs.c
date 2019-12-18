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
struct mlx5e_tirc_config {int dummy; } ;
struct mlx5e_priv {int /*<<< orphan*/  rss_params; } ;
struct TYPE_2__ {int /*<<< orphan*/  rqtn; } ;
struct mlx5e_hairpin {int /*<<< orphan*/ * indir_tirn; int /*<<< orphan*/  func_mdev; TYPE_1__ indir_rqt; int /*<<< orphan*/  tdn; struct mlx5e_priv* func_priv; } ;

/* Variables and functions */
 int MLX5E_NUM_INDIR_TIRS ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_TIRC_DISP_TYPE_INDIRECT ; 
 int /*<<< orphan*/  create_tir_in ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  disp_type ; 
 int /*<<< orphan*/  indirect_table ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_core_create_tir (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_destroy_tir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mlx5e_build_indir_tir_ctx_hash (int /*<<< orphan*/ *,struct mlx5e_tirc_config*,void*,int) ; 
 struct mlx5e_tirc_config mlx5e_tirc_get_default_config (int) ; 
 int /*<<< orphan*/  transport_domain ; 

__attribute__((used)) static int mlx5e_hairpin_create_indirect_tirs(struct mlx5e_hairpin *hp)
{
	struct mlx5e_priv *priv = hp->func_priv;
	u32 in[MLX5_ST_SZ_DW(create_tir_in)];
	int tt, i, err;
	void *tirc;

	for (tt = 0; tt < MLX5E_NUM_INDIR_TIRS; tt++) {
		struct mlx5e_tirc_config ttconfig = mlx5e_tirc_get_default_config(tt);

		memset(in, 0, MLX5_ST_SZ_BYTES(create_tir_in));
		tirc = MLX5_ADDR_OF(create_tir_in, in, ctx);

		MLX5_SET(tirc, tirc, transport_domain, hp->tdn);
		MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_INDIRECT);
		MLX5_SET(tirc, tirc, indirect_table, hp->indir_rqt.rqtn);
		mlx5e_build_indir_tir_ctx_hash(&priv->rss_params, &ttconfig, tirc, false);

		err = mlx5_core_create_tir(hp->func_mdev, in,
					   MLX5_ST_SZ_BYTES(create_tir_in), &hp->indir_tirn[tt]);
		if (err) {
			mlx5_core_warn(hp->func_mdev, "create indirect tirs failed, %d\n", err);
			goto err_destroy_tirs;
		}
	}
	return 0;

err_destroy_tirs:
	for (i = 0; i < tt; i++)
		mlx5_core_destroy_tir(hp->func_mdev, hp->indir_tirn[i]);
	return err;
}