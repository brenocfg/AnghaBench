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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_dpipe_headers_unregister (struct devlink*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_adj_table_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_erif_table_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_host4_table_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_host6_table_fini (struct mlxsw_sp*) ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 

void mlxsw_sp_dpipe_fini(struct mlxsw_sp *mlxsw_sp)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	mlxsw_sp_dpipe_adj_table_fini(mlxsw_sp);
	mlxsw_sp_dpipe_host6_table_fini(mlxsw_sp);
	mlxsw_sp_dpipe_host4_table_fini(mlxsw_sp);
	mlxsw_sp_dpipe_erif_table_fini(mlxsw_sp);
	devlink_dpipe_headers_unregister(devlink);
}