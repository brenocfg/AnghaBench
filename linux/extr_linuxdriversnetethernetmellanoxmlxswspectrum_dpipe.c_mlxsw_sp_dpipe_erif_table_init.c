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
 int /*<<< orphan*/  MLXSW_SP_DPIPE_TABLE_NAME_ERIF ; 
 int devlink_dpipe_table_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlxsw_sp*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_erif_ops ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_dpipe_erif_table_init(struct mlxsw_sp *mlxsw_sp)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	return devlink_dpipe_table_register(devlink,
					    MLXSW_SP_DPIPE_TABLE_NAME_ERIF,
					    &mlxsw_sp_erif_ops,
					    mlxsw_sp, false);
}