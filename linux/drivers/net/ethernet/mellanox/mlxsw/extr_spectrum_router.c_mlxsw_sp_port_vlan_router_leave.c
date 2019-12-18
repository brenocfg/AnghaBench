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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp_port_vlan {struct mlxsw_sp_fid* fid; int /*<<< orphan*/  vid; struct mlxsw_sp_port* mlxsw_sp_port; } ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp_fid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_BLOCKING ; 
 scalar_t__ MLXSW_SP_FID_TYPE_RFID ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_port_vid_unmap (struct mlxsw_sp_fid*,struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_put (struct mlxsw_sp_fid*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_fid_rif (struct mlxsw_sp_fid*) ; 
 scalar_t__ mlxsw_sp_fid_type (struct mlxsw_sp_fid*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vid_learning_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vid_stp_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_subport_put (struct mlxsw_sp_rif*) ; 

void
mlxsw_sp_port_vlan_router_leave(struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
{
	struct mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	struct mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;
	struct mlxsw_sp_rif *rif = mlxsw_sp_fid_rif(fid);
	u16 vid = mlxsw_sp_port_vlan->vid;

	if (WARN_ON(mlxsw_sp_fid_type(fid) != MLXSW_SP_FID_TYPE_RFID))
		return;

	mlxsw_sp_port_vlan->fid = NULL;
	mlxsw_sp_port_vid_stp_set(mlxsw_sp_port, vid, BR_STATE_BLOCKING);
	mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, true);
	mlxsw_sp_fid_port_vid_unmap(fid, mlxsw_sp_port, vid);
	mlxsw_sp_fid_put(fid);
	mlxsw_sp_rif_subport_put(rif);
}