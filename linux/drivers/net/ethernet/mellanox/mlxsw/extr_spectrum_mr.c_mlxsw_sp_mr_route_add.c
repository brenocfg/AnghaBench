#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mr_mfc {int dummy; } ;
struct mlxsw_sp_mr_table {int /*<<< orphan*/  route_ht; int /*<<< orphan*/  route_list; TYPE_3__* mlxsw_sp; TYPE_1__* ops; } ;
struct mlxsw_sp_mr_route {int /*<<< orphan*/  node; int /*<<< orphan*/  ht_node; int /*<<< orphan*/  route_priv; int /*<<< orphan*/  key; } ;
struct TYPE_6__ {TYPE_2__* bus_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* is_route_valid ) (struct mlxsw_sp_mr_table*,struct mr_mfc*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_mr_route*) ; 
 int PTR_ERR (struct mlxsw_sp_mr_route*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_mfc_offload_update (struct mlxsw_sp_mr_route*) ; 
 struct mlxsw_sp_mr_route* mlxsw_sp_mr_route_create (struct mlxsw_sp_mr_table*,struct mr_mfc*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_route_destroy (struct mlxsw_sp_mr_table*,struct mlxsw_sp_mr_route*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_route_ht_params ; 
 int mlxsw_sp_mr_route_write (struct mlxsw_sp_mr_table*,struct mlxsw_sp_mr_route*,int) ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_mr_route* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_mr_table*,struct mr_mfc*) ; 

int mlxsw_sp_mr_route_add(struct mlxsw_sp_mr_table *mr_table,
			  struct mr_mfc *mfc, bool replace)
{
	struct mlxsw_sp_mr_route *mr_orig_route = NULL;
	struct mlxsw_sp_mr_route *mr_route;
	int err;

	if (!mr_table->ops->is_route_valid(mr_table, mfc))
		return -EINVAL;

	/* Create a new route */
	mr_route = mlxsw_sp_mr_route_create(mr_table, mfc);
	if (IS_ERR(mr_route))
		return PTR_ERR(mr_route);

	/* Find any route with a matching key */
	mr_orig_route = rhashtable_lookup_fast(&mr_table->route_ht,
					       &mr_route->key,
					       mlxsw_sp_mr_route_ht_params);
	if (replace) {
		/* On replace case, make the route point to the new route_priv.
		 */
		if (WARN_ON(!mr_orig_route)) {
			err = -ENOENT;
			goto err_no_orig_route;
		}
		mr_route->route_priv = mr_orig_route->route_priv;
	} else if (mr_orig_route) {
		/* On non replace case, if another route with the same key was
		 * found, abort, as duplicate routes are used for proxy routes.
		 */
		dev_warn(mr_table->mlxsw_sp->bus_info->dev,
			 "Offloading proxy routes is not supported.\n");
		err = -EINVAL;
		goto err_duplicate_route;
	}

	/* Put it in the table data-structures */
	list_add_tail(&mr_route->node, &mr_table->route_list);
	err = rhashtable_insert_fast(&mr_table->route_ht,
				     &mr_route->ht_node,
				     mlxsw_sp_mr_route_ht_params);
	if (err)
		goto err_rhashtable_insert;

	/* Write the route to the hardware */
	err = mlxsw_sp_mr_route_write(mr_table, mr_route, replace);
	if (err)
		goto err_mr_route_write;

	/* Destroy the original route */
	if (replace) {
		rhashtable_remove_fast(&mr_table->route_ht,
				       &mr_orig_route->ht_node,
				       mlxsw_sp_mr_route_ht_params);
		list_del(&mr_orig_route->node);
		mlxsw_sp_mr_route_destroy(mr_table, mr_orig_route);
	}

	mlxsw_sp_mr_mfc_offload_update(mr_route);
	return 0;

err_mr_route_write:
	rhashtable_remove_fast(&mr_table->route_ht, &mr_route->ht_node,
			       mlxsw_sp_mr_route_ht_params);
err_rhashtable_insert:
	list_del(&mr_route->node);
err_no_orig_route:
err_duplicate_route:
	mlxsw_sp_mr_route_destroy(mr_table, mr_route);
	return err;
}