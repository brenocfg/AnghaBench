#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int /*<<< orphan*/  params; } ;
struct TYPE_10__ {int /*<<< orphan*/  rqtn; } ;
struct mlx5e_priv {TYPE_4__ channels; TYPE_5__ indir_rqt; TYPE_3__* mdev; } ;
typedef  enum mlx5e_traffic_types { ____Placeholder_mlx5e_traffic_types } mlx5e_traffic_types ;
struct TYPE_6__ {int /*<<< orphan*/  tdn; } ;
struct TYPE_7__ {TYPE_1__ td; } ;
struct TYPE_8__ {TYPE_2__ mlx5e_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_TIRC_DISP_TYPE_INDIRECT ; 
 int /*<<< orphan*/  disp_type ; 
 int /*<<< orphan*/  indirect_table ; 
 int /*<<< orphan*/  mlx5e_build_indir_tir_ctx_hash (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5e_build_tir_ctx_lro (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_domain ; 

__attribute__((used)) static void mlx5e_build_indir_tir_ctx(struct mlx5e_priv *priv,
				      enum mlx5e_traffic_types tt,
				      u32 *tirc)
{
	MLX5_SET(tirc, tirc, transport_domain, priv->mdev->mlx5e_res.td.tdn);

	mlx5e_build_tir_ctx_lro(&priv->channels.params, tirc);

	MLX5_SET(tirc, tirc, disp_type, MLX5_TIRC_DISP_TYPE_INDIRECT);
	MLX5_SET(tirc, tirc, indirect_table, priv->indir_rqt.rqtn);
	mlx5e_build_indir_tir_ctx_hash(&priv->channels.params, tt, tirc, false);
}