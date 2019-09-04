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
struct mlx5e_flow_table {int /*<<< orphan*/ * t; scalar_t__ num_groups; } ;
struct mlx5e_l2_table {struct mlx5e_flow_table ft; } ;
struct TYPE_2__ {int /*<<< orphan*/  ns; struct mlx5e_l2_table l2; } ;
struct mlx5e_priv {TYPE_1__ fs; } ;
struct mlx5_flow_table_attr {int /*<<< orphan*/  prio; int /*<<< orphan*/  level; int /*<<< orphan*/  max_fte; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5E_L2_FT_LEVEL ; 
 int /*<<< orphan*/  MLX5E_L2_TABLE_SIZE ; 
 int /*<<< orphan*/  MLX5E_NIC_PRIO ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mlx5_create_flow_table (int /*<<< orphan*/ ,struct mlx5_flow_table_attr*) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ *) ; 
 int mlx5e_create_l2_table_groups (struct mlx5e_l2_table*) ; 

__attribute__((used)) static int mlx5e_create_l2_table(struct mlx5e_priv *priv)
{
	struct mlx5e_l2_table *l2_table = &priv->fs.l2;
	struct mlx5e_flow_table *ft = &l2_table->ft;
	struct mlx5_flow_table_attr ft_attr = {};
	int err;

	ft->num_groups = 0;

	ft_attr.max_fte = MLX5E_L2_TABLE_SIZE;
	ft_attr.level = MLX5E_L2_FT_LEVEL;
	ft_attr.prio = MLX5E_NIC_PRIO;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &ft_attr);
	if (IS_ERR(ft->t)) {
		err = PTR_ERR(ft->t);
		ft->t = NULL;
		return err;
	}

	err = mlx5e_create_l2_table_groups(l2_table);
	if (err)
		goto err_destroy_flow_table;

	return 0;

err_destroy_flow_table:
	mlx5_destroy_flow_table(ft->t);
	ft->t = NULL;

	return err;
}