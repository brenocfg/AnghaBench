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
struct mlxsw_sp_rif {int /*<<< orphan*/  fid; TYPE_1__* dev; int /*<<< orphan*/  mlxsw_sp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fid_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_rif_set (int /*<<< orphan*/ ,struct mlxsw_sp_rif*) ; 
 int mlxsw_sp_rif_fdb_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlxsw_sp_rif_subport_op (struct mlxsw_sp_rif*,int) ; 

__attribute__((used)) static int mlxsw_sp_rif_subport_configure(struct mlxsw_sp_rif *rif)
{
	int err;

	err = mlxsw_sp_rif_subport_op(rif, true);
	if (err)
		return err;

	err = mlxsw_sp_rif_fdb_op(rif->mlxsw_sp, rif->dev->dev_addr,
				  mlxsw_sp_fid_index(rif->fid), true);
	if (err)
		goto err_rif_fdb_op;

	mlxsw_sp_fid_rif_set(rif->fid, rif);
	return 0;

err_rif_fdb_op:
	mlxsw_sp_rif_subport_op(rif, false);
	return err;
}