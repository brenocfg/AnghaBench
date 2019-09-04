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
struct TYPE_2__ {int /*<<< orphan*/  inner_ttc; int /*<<< orphan*/  ttc; } ;
struct mlx5e_priv {TYPE_1__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_arfs_destroy_tables (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_inner_ttc_table (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_ttc_table (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5i_destroy_flow_steering(struct mlx5e_priv *priv)
{
	mlx5e_destroy_ttc_table(priv, &priv->fs.ttc);
	mlx5e_destroy_inner_ttc_table(priv, &priv->fs.inner_ttc);
	mlx5e_arfs_destroy_tables(priv);
}