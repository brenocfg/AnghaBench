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
struct mlxsw_sp_mr_tcam_erif_list {int dummy; } ;
struct mlxsw_sp_mr_tcam_route {int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  irif_index; int /*<<< orphan*/  action; struct mlxsw_sp_mr_tcam_erif_list erif_list; struct mlxsw_afa_block* afa_block; int /*<<< orphan*/  key; int /*<<< orphan*/  priv; int /*<<< orphan*/  counter_index; } ;
struct mlxsw_sp_mr_tcam_ops {int (* route_update ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_afa_block*) ;} ;
struct mlxsw_sp_mr_route_info {int /*<<< orphan*/  min_mtu; int /*<<< orphan*/  irif_index; int /*<<< orphan*/  route_action; } ;
struct mlxsw_sp {struct mlxsw_sp_mr_tcam_ops* mr_tcam_ops; } ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_afa_block*) ; 
 int PTR_ERR (struct mlxsw_afa_block*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_erif_list_flush (struct mlxsw_sp*,struct mlxsw_sp_mr_tcam_erif_list*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_erif_list_init (struct mlxsw_sp_mr_tcam_erif_list*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_erif_list_move (struct mlxsw_sp_mr_tcam_erif_list*,struct mlxsw_sp_mr_tcam_erif_list*) ; 
 struct mlxsw_afa_block* mlxsw_sp_mr_tcam_afa_block_create (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_mr_tcam_erif_list*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_tcam_afa_block_destroy (struct mlxsw_afa_block*) ; 
 int mlxsw_sp_mr_tcam_erif_populate (struct mlxsw_sp*,struct mlxsw_sp_mr_tcam_erif_list*,struct mlxsw_sp_mr_route_info*) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_afa_block*) ; 

__attribute__((used)) static int
mlxsw_sp_mr_tcam_route_update(struct mlxsw_sp *mlxsw_sp, void *route_priv,
			      struct mlxsw_sp_mr_route_info *route_info)
{
	const struct mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	struct mlxsw_sp_mr_tcam_route *route = route_priv;
	struct mlxsw_sp_mr_tcam_erif_list erif_list;
	struct mlxsw_afa_block *afa_block;
	int err;

	/* Create a new erif_list */
	mlxsw_sp_mr_erif_list_init(&erif_list);
	err = mlxsw_sp_mr_tcam_erif_populate(mlxsw_sp, &erif_list, route_info);
	if (err)
		goto err_erif_populate;

	/* Create the flexible action block pointing to the new erif_list */
	afa_block = mlxsw_sp_mr_tcam_afa_block_create(mlxsw_sp,
						      route_info->route_action,
						      route_info->irif_index,
						      route->counter_index,
						      route_info->min_mtu,
						      &erif_list);
	if (IS_ERR(afa_block)) {
		err = PTR_ERR(afa_block);
		goto err_afa_block_create;
	}

	/* Update the TCAM route entry */
	err = ops->route_update(mlxsw_sp, route->priv, &route->key, afa_block);
	if (err)
		goto err_route_write;

	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
	mlxsw_sp_mr_erif_list_flush(mlxsw_sp, &route->erif_list);
	route->afa_block = afa_block;
	mlxsw_sp_mr_erif_list_move(&route->erif_list, &erif_list);
	route->action = route_info->route_action;
	route->irif_index = route_info->irif_index;
	route->min_mtu = route_info->min_mtu;
	return 0;

err_route_write:
	mlxsw_sp_mr_tcam_afa_block_destroy(afa_block);
err_afa_block_create:
err_erif_populate:
	mlxsw_sp_mr_erif_list_flush(mlxsw_sp, &erif_list);
	return err;
}