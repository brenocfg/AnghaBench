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
typedef  size_t u8 ;
struct TYPE_4__ {int /*<<< orphan*/  shaper_dw; } ;
struct TYPE_3__ {int /*<<< orphan*/  update_dw; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  vlans_list; int /*<<< orphan*/  pcpu_stats; int /*<<< orphan*/  sample; TYPE_2__ ptp; TYPE_1__ periodic_hw_stats; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; struct mlxsw_sp_port** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PORT_SWID_DISABLED_PORT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_port_clear (int /*<<< orphan*/ ,size_t,struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_core_port_fini (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mlxsw_sp_port_dcb_fini (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_fids_fini (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_module_unmap (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_nve_fini (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_ptp_clear (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_swid_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_tc_mc_mode_set (struct mlxsw_sp_port*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_flush (struct mlxsw_sp_port*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_tc_qdisc_fini (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_port_remove(struct mlxsw_sp *mlxsw_sp, u8 local_port)
{
	struct mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp->ports[local_port];

	cancel_delayed_work_sync(&mlxsw_sp_port->periodic_hw_stats.update_dw);
	cancel_delayed_work_sync(&mlxsw_sp_port->ptp.shaper_dw);
	mlxsw_sp_port_ptp_clear(mlxsw_sp_port);
	mlxsw_core_port_clear(mlxsw_sp->core, local_port, mlxsw_sp);
	unregister_netdev(mlxsw_sp_port->dev); /* This calls ndo_stop */
	mlxsw_sp->ports[local_port] = NULL;
	mlxsw_sp_port_vlan_flush(mlxsw_sp_port, true);
	mlxsw_sp_port_nve_fini(mlxsw_sp_port);
	mlxsw_sp_tc_qdisc_fini(mlxsw_sp_port);
	mlxsw_sp_port_fids_fini(mlxsw_sp_port);
	mlxsw_sp_port_dcb_fini(mlxsw_sp_port);
	mlxsw_sp_port_tc_mc_mode_set(mlxsw_sp_port, false);
	mlxsw_sp_port_swid_set(mlxsw_sp_port, MLXSW_PORT_SWID_DISABLED_PORT);
	mlxsw_sp_port_module_unmap(mlxsw_sp_port);
	kfree(mlxsw_sp_port->sample);
	free_percpu(mlxsw_sp_port->pcpu_stats);
	WARN_ON_ONCE(!list_empty(&mlxsw_sp_port->vlans_list));
	free_netdev(mlxsw_sp_port->dev);
	mlxsw_core_port_fini(mlxsw_sp->core, local_port);
}