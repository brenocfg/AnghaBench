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
struct TYPE_2__ {int /*<<< orphan*/  rqtn; } ;
struct mlx5e_priv {int /*<<< orphan*/  rss_params; TYPE_1__ indir_rqt; } ;
typedef  enum mlx5e_traffic_types { ____Placeholder_mlx5e_traffic_types } mlx5e_traffic_types ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_build_indir_tir_ctx_common (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_indir_tir_ctx_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * tirc_default_config ; 

__attribute__((used)) static void mlx5e_build_inner_indir_tir_ctx(struct mlx5e_priv *priv,
					    enum mlx5e_traffic_types tt,
					    u32 *tirc)
{
	mlx5e_build_indir_tir_ctx_common(priv, priv->indir_rqt.rqtn, tirc);
	mlx5e_build_indir_tir_ctx_hash(&priv->rss_params,
				       &tirc_default_config[tt], tirc, true);
}