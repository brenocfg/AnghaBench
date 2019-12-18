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
struct mlxsw_sp_mr_route {scalar_t__ route_action; } ;

/* Variables and functions */
 scalar_t__ MLXSW_SP_MR_ROUTE_ACTION_TRAP ; 
 int /*<<< orphan*/  mlxsw_sp_mr_mfc_offload_set (struct mlxsw_sp_mr_route*,int) ; 

__attribute__((used)) static void mlxsw_sp_mr_mfc_offload_update(struct mlxsw_sp_mr_route *mr_route)
{
	bool offload;

	offload = mr_route->route_action != MLXSW_SP_MR_ROUTE_ACTION_TRAP;
	mlxsw_sp_mr_mfc_offload_set(mr_route, offload);
}