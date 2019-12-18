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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  rqn; } ;
struct mlx5e_redirect_rqt_param {int is_rss; TYPE_1__ member_1; } ;
struct TYPE_8__ {int /*<<< orphan*/  rqtn; scalar_t__ enabled; } ;
struct mlx5e_priv {int max_nch; TYPE_3__* direct_tir; TYPE_4__ indir_rqt; } ;
struct TYPE_6__ {int /*<<< orphan*/  rqtn; int /*<<< orphan*/  enabled; } ;
struct TYPE_7__ {TYPE_2__ rqt; } ;

/* Variables and functions */
 int MLX5E_INDIR_RQT_SIZE ; 
 int /*<<< orphan*/  mlx5e_get_direct_rqn (struct mlx5e_priv*,int,struct mlx5e_redirect_rqt_param) ; 
 int /*<<< orphan*/  mlx5e_redirect_rqt (struct mlx5e_priv*,int /*<<< orphan*/ ,int,struct mlx5e_redirect_rqt_param) ; 

__attribute__((used)) static void mlx5e_redirect_rqts(struct mlx5e_priv *priv,
				struct mlx5e_redirect_rqt_param rrp)
{
	u32 rqtn;
	int ix;

	if (priv->indir_rqt.enabled) {
		/* RSS RQ table */
		rqtn = priv->indir_rqt.rqtn;
		mlx5e_redirect_rqt(priv, rqtn, MLX5E_INDIR_RQT_SIZE, rrp);
	}

	for (ix = 0; ix < priv->max_nch; ix++) {
		struct mlx5e_redirect_rqt_param direct_rrp = {
			.is_rss = false,
			{
				.rqn    = mlx5e_get_direct_rqn(priv, ix, rrp)
			},
		};

		/* Direct RQ Tables */
		if (!priv->direct_tir[ix].rqt.enabled)
			continue;

		rqtn = priv->direct_tir[ix].rqt.rqtn;
		mlx5e_redirect_rqt(priv, rqtn, 1, direct_rrp);
	}
}