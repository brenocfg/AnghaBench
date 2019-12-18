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
struct mlxsw_sp_port {size_t local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
struct TYPE_2__ {scalar_t__* port_fid_mappings; } ;

/* Variables and functions */
 int mlxsw_sp_port_vp_mode_set (struct mlxsw_sp_port*,int) ; 

int mlxsw_sp_port_fids_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	/* Track number of FIDs configured on the port with mapping type
	 * PORT_VID_TO_FID, so that we know when to transition the port
	 * back to non-virtual (VLAN) mode.
	 */
	mlxsw_sp->fid_core->port_fid_mappings[mlxsw_sp_port->local_port] = 0;

	return mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, false);
}