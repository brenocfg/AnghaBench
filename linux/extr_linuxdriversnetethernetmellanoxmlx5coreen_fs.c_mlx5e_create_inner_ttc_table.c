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
struct ttc_params {int /*<<< orphan*/  ft_attr; } ;
struct mlx5e_flow_table {int /*<<< orphan*/ * t; } ;
struct mlx5e_ttc_table {struct mlx5e_flow_table ft; } ;
struct TYPE_2__ {int /*<<< orphan*/  ns; } ;
struct mlx5e_priv {TYPE_1__ fs; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mlx5_create_flow_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5e_create_inner_ttc_table_groups (struct mlx5e_ttc_table*) ; 
 int /*<<< orphan*/  mlx5e_destroy_flow_table (struct mlx5e_flow_table*) ; 
 int mlx5e_generate_inner_ttc_table_rules (struct mlx5e_priv*,struct ttc_params*,struct mlx5e_ttc_table*) ; 
 int /*<<< orphan*/  mlx5e_tunnel_inner_ft_supported (int /*<<< orphan*/ ) ; 

int mlx5e_create_inner_ttc_table(struct mlx5e_priv *priv, struct ttc_params *params,
				 struct mlx5e_ttc_table *ttc)
{
	struct mlx5e_flow_table *ft = &ttc->ft;
	int err;

	if (!mlx5e_tunnel_inner_ft_supported(priv->mdev))
		return 0;

	ft->t = mlx5_create_flow_table(priv->fs.ns, &params->ft_attr);
	if (IS_ERR(ft->t)) {
		err = PTR_ERR(ft->t);
		ft->t = NULL;
		return err;
	}

	err = mlx5e_create_inner_ttc_table_groups(ttc);
	if (err)
		goto err;

	err = mlx5e_generate_inner_ttc_table_rules(priv, params, ttc);
	if (err)
		goto err;

	return 0;

err:
	mlx5e_destroy_flow_table(ft);
	return err;
}