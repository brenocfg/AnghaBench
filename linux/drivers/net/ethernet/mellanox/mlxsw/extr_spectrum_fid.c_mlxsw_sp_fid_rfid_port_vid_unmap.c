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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_port {size_t local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
struct TYPE_2__ {int* port_fid_mappings; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_port_vlan_mode_trans (struct mlxsw_sp_port*) ; 

__attribute__((used)) static void
mlxsw_sp_fid_rfid_port_vid_unmap(struct mlxsw_sp_fid *fid,
				 struct mlxsw_sp_port *mlxsw_sp_port, u16 vid)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;

	if (mlxsw_sp->fid_core->port_fid_mappings[local_port] == 1)
		mlxsw_sp_port_vlan_mode_trans(mlxsw_sp_port);
	mlxsw_sp->fid_core->port_fid_mappings[local_port]--;
}