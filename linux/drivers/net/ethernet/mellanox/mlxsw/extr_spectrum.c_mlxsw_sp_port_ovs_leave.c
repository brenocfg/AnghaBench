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
typedef  int u16 ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int VLAN_N_VID ; 
 int /*<<< orphan*/  mlxsw_sp_port_stp_set (struct mlxsw_sp_port*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vid_learning_set (struct mlxsw_sp_port*,int,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_set (struct mlxsw_sp_port*,int,int,int,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vp_mode_set (struct mlxsw_sp_port*,int) ; 

__attribute__((used)) static void mlxsw_sp_port_ovs_leave(struct mlxsw_sp_port *mlxsw_sp_port)
{
	u16 vid;

	for (vid = VLAN_N_VID - 1; vid >= 1; vid--)
		mlxsw_sp_port_vid_learning_set(mlxsw_sp_port,
					       vid, true);

	mlxsw_sp_port_vlan_set(mlxsw_sp_port, 1, VLAN_N_VID - 2,
			       false, false);
	mlxsw_sp_port_stp_set(mlxsw_sp_port, false);
	mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, false);
}