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
struct mlx5e_rep_priv {int /*<<< orphan*/  vport_rx_rule; } ;
struct TYPE_2__ {int /*<<< orphan*/  ttc; } ;
struct mlx5e_priv {int /*<<< orphan*/  drop_rq; int /*<<< orphan*/  indir_rqt; int /*<<< orphan*/  direct_tir; TYPE_1__ fs; struct mlx5e_rep_priv* ppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_close_drop_rq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_rqts (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_tirs (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_indirect_tirs (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  mlx5e_destroy_rqt (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_ttc_table (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_cleanup_rep_rx(struct mlx5e_priv *priv)
{
	struct mlx5e_rep_priv *rpriv = priv->ppriv;

	mlx5_del_flow_rules(rpriv->vport_rx_rule);
	mlx5e_destroy_ttc_table(priv, &priv->fs.ttc);
	mlx5e_destroy_direct_tirs(priv, priv->direct_tir);
	mlx5e_destroy_indirect_tirs(priv, false);
	mlx5e_destroy_direct_rqts(priv, priv->direct_tir);
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
	mlx5e_close_drop_rq(&priv->drop_rq);
}