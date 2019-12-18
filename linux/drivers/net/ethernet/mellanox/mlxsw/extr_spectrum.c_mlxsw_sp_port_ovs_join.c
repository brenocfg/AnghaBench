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
 int mlxsw_sp_port_stp_set (struct mlxsw_sp_port*,int) ; 
 int mlxsw_sp_port_vid_learning_set (struct mlxsw_sp_port*,int,int) ; 
 int mlxsw_sp_port_vlan_set (struct mlxsw_sp_port*,int,int,int,int) ; 
 int mlxsw_sp_port_vp_mode_set (struct mlxsw_sp_port*,int) ; 

__attribute__((used)) static int mlxsw_sp_port_ovs_join(struct mlxsw_sp_port *mlxsw_sp_port)
{
	u16 vid = 1;
	int err;

	err = mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, true);
	if (err)
		return err;
	err = mlxsw_sp_port_stp_set(mlxsw_sp_port, true);
	if (err)
		goto err_port_stp_set;
	err = mlxsw_sp_port_vlan_set(mlxsw_sp_port, 1, VLAN_N_VID - 2,
				     true, false);
	if (err)
		goto err_port_vlan_set;

	for (; vid <= VLAN_N_VID - 1; vid++) {
		err = mlxsw_sp_port_vid_learning_set(mlxsw_sp_port,
						     vid, false);
		if (err)
			goto err_vid_learning_set;
	}

	return 0;

err_vid_learning_set:
	for (vid--; vid >= 1; vid--)
		mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, true);
err_port_vlan_set:
	mlxsw_sp_port_stp_set(mlxsw_sp_port, false);
err_port_stp_set:
	mlxsw_sp_port_vp_mode_set(mlxsw_sp_port, false);
	return err;
}