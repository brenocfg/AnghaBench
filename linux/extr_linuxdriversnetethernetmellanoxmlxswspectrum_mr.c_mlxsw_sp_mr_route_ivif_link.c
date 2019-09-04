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
struct mlxsw_sp_mr_vif {int /*<<< orphan*/  route_ivif_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  vif_node; struct mlxsw_sp_mr_vif* mr_vif; struct mlxsw_sp_mr_route* mr_route; } ;
struct mlxsw_sp_mr_route {TYPE_1__ ivif; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_mr_route_ivif_link(struct mlxsw_sp_mr_route *mr_route,
					struct mlxsw_sp_mr_vif *mr_vif)
{
	mr_route->ivif.mr_route = mr_route;
	mr_route->ivif.mr_vif = mr_vif;
	list_add_tail(&mr_route->ivif.vif_node, &mr_vif->route_ivif_list);
}