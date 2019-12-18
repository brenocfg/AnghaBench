#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5e_priv {int /*<<< orphan*/  drop_rq; int /*<<< orphan*/  indir_rqt; int /*<<< orphan*/  direct_tir; int /*<<< orphan*/  xsk_tir; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_close_drop_rq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_rqts (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_tirs (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_flow_steering (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_indirect_tirs (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  mlx5e_destroy_q_counters (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_rqt (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_tc_nic_cleanup (struct mlx5e_priv*) ; 

__attribute__((used)) static void mlx5e_cleanup_nic_rx(struct mlx5e_priv *priv)
{
	mlx5e_tc_nic_cleanup(priv);
	mlx5e_destroy_flow_steering(priv);
	mlx5e_destroy_direct_tirs(priv, priv->xsk_tir);
	mlx5e_destroy_direct_rqts(priv, priv->xsk_tir);
	mlx5e_destroy_direct_tirs(priv, priv->direct_tir);
	mlx5e_destroy_indirect_tirs(priv, true);
	mlx5e_destroy_direct_rqts(priv, priv->direct_tir);
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
	mlx5e_close_drop_rq(&priv->drop_rq);
	mlx5e_destroy_q_counters(priv);
}