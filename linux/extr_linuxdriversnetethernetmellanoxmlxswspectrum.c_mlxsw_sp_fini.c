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
struct mlxsw_sp {int /*<<< orphan*/  netdevice_nb; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_afa_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_buffers_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_counter_pool_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_fids_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_lag_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_ports_remove (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_router_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_span_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_traps_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_fini(struct mlxsw_core *mlxsw_core)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_sp_ports_remove(mlxsw_sp);
	mlxsw_sp_dpipe_fini(mlxsw_sp);
	mlxsw_sp_acl_fini(mlxsw_sp);
	unregister_netdevice_notifier(&mlxsw_sp->netdevice_nb);
	mlxsw_sp_router_fini(mlxsw_sp);
	mlxsw_sp_afa_fini(mlxsw_sp);
	mlxsw_sp_counter_pool_fini(mlxsw_sp);
	mlxsw_sp_switchdev_fini(mlxsw_sp);
	mlxsw_sp_span_fini(mlxsw_sp);
	mlxsw_sp_lag_fini(mlxsw_sp);
	mlxsw_sp_buffers_fini(mlxsw_sp);
	mlxsw_sp_traps_fini(mlxsw_sp);
	mlxsw_sp_fids_fini(mlxsw_sp);
	mlxsw_sp_kvdl_fini(mlxsw_sp);
}