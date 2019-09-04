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
struct mlxsw_sp_mr_tcam_route {int action; struct mlxsw_afa_block* afa_block; int /*<<< orphan*/  key; int /*<<< orphan*/  priv; int /*<<< orphan*/  erif_list; int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  counter_index; int /*<<< orphan*/  irif_index; } ;
struct mlxsw_sp_mr_tcam_ops {int (* route_update ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_afa_block*) ;} ;
struct mlxsw_sp {struct mlxsw_sp_mr_tcam_ops* mr_tcam_ops; } ;
struct mlxsw_afa_block {int dummy; } ;
typedef  enum mlxsw_sp_mr_route_action { ____Placeholder_mlxsw_sp_mr_route_action } mlxsw_sp_mr_route_action ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_afa_block*) ; 
 int PTR_ERR (struct mlxsw_afa_block*) ; 
 struct mlxsw_afa_block* mlxsw_sp_mr_tcam_afa_block_create (struct mlxsw_sp*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_tcam_afa_block_destroy (struct mlxsw_afa_block*) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_afa_block*) ; 

__attribute__((used)) static int
mlxsw_sp_mr_tcam_route_action_update(struct mlxsw_sp *mlxsw_sp,
				     void *route_priv,
				     enum mlxsw_sp_mr_route_action route_action)
{
	const struct mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	struct mlxsw_sp_mr_tcam_route *route = route_priv;
	struct mlxsw_afa_block *afa_block;
	int err;

	/* Create a new flexible action block */
	afa_block = mlxsw_sp_mr_tcam_afa_block_create(mlxsw_sp, route_action,
						      route->irif_index,
						      route->counter_index,
						      route->min_mtu,
						      &route->erif_list);
	if (IS_ERR(afa_block))
		return PTR_ERR(afa_block);

	/* Update the TCAM route entry */
	err = ops->route_update(mlxsw_sp, route->priv, &route->key, afa_block);
	if (err)
		goto err;

	/* Delete the old one */
	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
	route->afa_block = afa_block;
	route->action = route_action;
	return 0;
err:
	mlxsw_sp_mr_tcam_afa_block_destroy(afa_block);
	return err;
}