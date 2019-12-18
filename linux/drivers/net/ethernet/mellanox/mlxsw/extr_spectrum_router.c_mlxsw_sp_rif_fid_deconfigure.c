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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_rif {struct mlxsw_sp_fid* fid; TYPE_1__* dev; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_RITR_FID_IF ; 
 int /*<<< orphan*/  MLXSW_SP_FLOOD_TYPE_BC ; 
 int /*<<< orphan*/  MLXSW_SP_FLOOD_TYPE_MC ; 
 int /*<<< orphan*/  mlxsw_sp_fid_flood_set (struct mlxsw_sp_fid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_index (struct mlxsw_sp_fid*) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_rif_set (struct mlxsw_sp_fid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_fdb_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_macvlan_flush (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_vlan_fid_op (struct mlxsw_sp_rif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_router_port (struct mlxsw_sp*) ; 

__attribute__((used)) static void mlxsw_sp_rif_fid_deconfigure(struct mlxsw_sp_rif *rif)
{
	u16 fid_index = mlxsw_sp_fid_index(rif->fid);
	struct mlxsw_sp *mlxsw_sp = rif->mlxsw_sp;
	struct mlxsw_sp_fid *fid = rif->fid;

	mlxsw_sp_fid_rif_set(fid, NULL);
	mlxsw_sp_rif_fdb_op(rif->mlxsw_sp, rif->dev->dev_addr,
			    mlxsw_sp_fid_index(fid), false);
	mlxsw_sp_rif_macvlan_flush(rif);
	mlxsw_sp_fid_flood_set(rif->fid, MLXSW_SP_FLOOD_TYPE_BC,
			       mlxsw_sp_router_port(mlxsw_sp), false);
	mlxsw_sp_fid_flood_set(rif->fid, MLXSW_SP_FLOOD_TYPE_MC,
			       mlxsw_sp_router_port(mlxsw_sp), false);
	mlxsw_sp_rif_vlan_fid_op(rif, MLXSW_REG_RITR_FID_IF, fid_index, false);
}