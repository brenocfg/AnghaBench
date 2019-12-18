#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp {TYPE_2__* router; } ;
struct TYPE_3__ {int /*<<< orphan*/  dw; } ;
struct TYPE_4__ {int /*<<< orphan*/  nexthop_probe_dw; TYPE_1__ neighs_update; int /*<<< orphan*/  neigh_ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_schedule_dw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_neigh_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_router_neighs_update_interval_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_router_neighs_update_work ; 
 int /*<<< orphan*/  mlxsw_sp_router_probe_unresolved_nexthops ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_neigh_init(struct mlxsw_sp *mlxsw_sp)
{
	int err;

	err = rhashtable_init(&mlxsw_sp->router->neigh_ht,
			      &mlxsw_sp_neigh_ht_params);
	if (err)
		return err;

	/* Initialize the polling interval according to the default
	 * table.
	 */
	mlxsw_sp_router_neighs_update_interval_init(mlxsw_sp);

	/* Create the delayed works for the activity_update */
	INIT_DELAYED_WORK(&mlxsw_sp->router->neighs_update.dw,
			  mlxsw_sp_router_neighs_update_work);
	INIT_DELAYED_WORK(&mlxsw_sp->router->nexthop_probe_dw,
			  mlxsw_sp_router_probe_unresolved_nexthops);
	mlxsw_core_schedule_dw(&mlxsw_sp->router->neighs_update.dw, 0);
	mlxsw_core_schedule_dw(&mlxsw_sp->router->nexthop_probe_dw, 0);
	return 0;
}