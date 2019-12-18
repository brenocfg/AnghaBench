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
struct mlxsw_sp_mr_table {int /*<<< orphan*/  route_ht; } ;
struct mlxsw_sp_mr_route {int /*<<< orphan*/  node; int /*<<< orphan*/  ht_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_mfc_offload_set (struct mlxsw_sp_mr_route*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_route_destroy (struct mlxsw_sp_mr_table*,struct mlxsw_sp_mr_route*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_route_erase (struct mlxsw_sp_mr_table*,struct mlxsw_sp_mr_route*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_route_ht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mlxsw_sp_mr_route_del(struct mlxsw_sp_mr_table *mr_table,
				    struct mlxsw_sp_mr_route *mr_route)
{
	mlxsw_sp_mr_mfc_offload_set(mr_route, false);
	mlxsw_sp_mr_route_erase(mr_table, mr_route);
	rhashtable_remove_fast(&mr_table->route_ht, &mr_route->ht_node,
			       mlxsw_sp_mr_route_ht_params);
	list_del(&mr_route->node);
	mlxsw_sp_mr_route_destroy(mr_table, mr_route);
}