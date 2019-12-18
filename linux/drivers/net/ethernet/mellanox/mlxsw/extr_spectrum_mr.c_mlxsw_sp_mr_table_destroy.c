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
struct mlxsw_sp_mr_table {int /*<<< orphan*/  route_ht; int /*<<< orphan*/  catchall_route_priv; int /*<<< orphan*/  node; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_mr {int /*<<< orphan*/  priv; TYPE_1__* mr_ops; } ;
struct mlxsw_sp {struct mlxsw_sp_mr* mr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* route_destroy ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_mr_table*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_table_empty (struct mlxsw_sp_mr_table*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlxsw_sp_mr_table_destroy(struct mlxsw_sp_mr_table *mr_table)
{
	struct mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	struct mlxsw_sp_mr *mr = mlxsw_sp->mr;

	WARN_ON(!mlxsw_sp_mr_table_empty(mr_table));
	list_del(&mr_table->node);
	mr->mr_ops->route_destroy(mlxsw_sp, mr->priv,
				  &mr_table->catchall_route_priv);
	rhashtable_destroy(&mr_table->route_ht);
	kfree(mr_table);
}