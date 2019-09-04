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
struct mlx5e_priv {int /*<<< orphan*/  indir_rqt; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_destroy_direct_rqts (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_direct_tirs (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_flow_steering (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_indirect_tirs (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_rqt (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_tc_nic_cleanup (struct mlx5e_priv*) ; 

__attribute__((used)) static void mlx5e_cleanup_nic_rx(struct mlx5e_priv *priv)
{
	mlx5e_tc_nic_cleanup(priv);
	mlx5e_destroy_flow_steering(priv);
	mlx5e_destroy_direct_tirs(priv);
	mlx5e_destroy_indirect_tirs(priv);
	mlx5e_destroy_direct_rqts(priv);
	mlx5e_destroy_rqt(priv, &priv->indir_rqt);
}