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
struct mlxsw_sp {scalar_t__ clock; TYPE_1__* ptp_ops; int /*<<< orphan*/  ptp_state; int /*<<< orphan*/  netdevice_nb; } ;
struct mlxsw_core {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clock_fini ) (scalar_t__) ;int /*<<< orphan*/  (* fini ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_afa_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_buffers_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_counter_pool_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_devlink_traps_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_fids_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_lag_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_ports_remove (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_router_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_span_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_traps_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_fini(struct mlxsw_core *mlxsw_core)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_sp_ports_remove(mlxsw_sp);
	mlxsw_sp_dpipe_fini(mlxsw_sp);
	unregister_netdevice_notifier(&mlxsw_sp->netdevice_nb);
	if (mlxsw_sp->clock) {
		mlxsw_sp->ptp_ops->fini(mlxsw_sp->ptp_state);
		mlxsw_sp->ptp_ops->clock_fini(mlxsw_sp->clock);
	}
	mlxsw_sp_router_fini(mlxsw_sp);
	mlxsw_sp_acl_fini(mlxsw_sp);
	mlxsw_sp_nve_fini(mlxsw_sp);
	mlxsw_sp_afa_fini(mlxsw_sp);
	mlxsw_sp_counter_pool_fini(mlxsw_sp);
	mlxsw_sp_switchdev_fini(mlxsw_sp);
	mlxsw_sp_span_fini(mlxsw_sp);
	mlxsw_sp_lag_fini(mlxsw_sp);
	mlxsw_sp_buffers_fini(mlxsw_sp);
	mlxsw_sp_devlink_traps_fini(mlxsw_sp);
	mlxsw_sp_traps_fini(mlxsw_sp);
	mlxsw_sp_fids_fini(mlxsw_sp);
	mlxsw_sp_kvdl_fini(mlxsw_sp);
}