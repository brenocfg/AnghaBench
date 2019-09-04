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
struct mlxsw_sp_mr_vif {int /*<<< orphan*/  route_evif_list; } ;
struct mlxsw_sp_mr_route_vif_entry {int /*<<< orphan*/  vif_node; int /*<<< orphan*/  route_node; struct mlxsw_sp_mr_vif* mr_vif; struct mlxsw_sp_mr_route* mr_route; } ;
struct mlxsw_sp_mr_route {int /*<<< orphan*/  evif_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlxsw_sp_mr_route_vif_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_mr_route_evif_link(struct mlxsw_sp_mr_route *mr_route,
				       struct mlxsw_sp_mr_vif *mr_vif)
{
	struct mlxsw_sp_mr_route_vif_entry *rve;

	rve = kzalloc(sizeof(*rve), GFP_KERNEL);
	if (!rve)
		return -ENOMEM;
	rve->mr_route = mr_route;
	rve->mr_vif = mr_vif;
	list_add_tail(&rve->route_node, &mr_route->evif_list);
	list_add_tail(&rve->vif_node, &mr_vif->route_evif_list);
	return 0;
}