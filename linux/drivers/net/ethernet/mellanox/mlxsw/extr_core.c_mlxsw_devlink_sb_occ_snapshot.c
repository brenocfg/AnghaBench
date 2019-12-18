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
struct mlxsw_driver {int (* sb_occ_snapshot ) (struct mlxsw_core*,unsigned int) ;} ;
struct mlxsw_core {struct mlxsw_driver* driver; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct mlxsw_core* devlink_priv (struct devlink*) ; 
 int stub1 (struct mlxsw_core*,unsigned int) ; 

__attribute__((used)) static int mlxsw_devlink_sb_occ_snapshot(struct devlink *devlink,
					 unsigned int sb_index)
{
	struct mlxsw_core *mlxsw_core = devlink_priv(devlink);
	struct mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	if (!mlxsw_driver->sb_occ_snapshot)
		return -EOPNOTSUPP;
	return mlxsw_driver->sb_occ_snapshot(mlxsw_core, sb_index);
}