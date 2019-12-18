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
struct mlxsw_sp_rif {TYPE_1__* dev; int /*<<< orphan*/  mlxsw_sp; struct mlxsw_sp_fid* fid; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fid_index (struct mlxsw_sp_fid*) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_rif_set (struct mlxsw_sp_fid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_fdb_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_macvlan_flush (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_subport_op (struct mlxsw_sp_rif*,int) ; 

__attribute__((used)) static void mlxsw_sp_rif_subport_deconfigure(struct mlxsw_sp_rif *rif)
{
	struct mlxsw_sp_fid *fid = rif->fid;

	mlxsw_sp_fid_rif_set(fid, NULL);
	mlxsw_sp_rif_fdb_op(rif->mlxsw_sp, rif->dev->dev_addr,
			    mlxsw_sp_fid_index(fid), false);
	mlxsw_sp_rif_macvlan_flush(rif);
	mlxsw_sp_rif_subport_op(rif, false);
}