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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_driver {int (* sb_port_pool_get ) (struct mlxsw_core_port*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct mlxsw_core_port {int dummy; } ;
struct mlxsw_core {struct mlxsw_driver* driver; } ;
struct devlink_port {int /*<<< orphan*/  devlink; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct mlxsw_core_port* __dl_port (struct devlink_port*) ; 
 struct mlxsw_core* devlink_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_port_check (struct mlxsw_core_port*) ; 
 int stub1 (struct mlxsw_core_port*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_devlink_sb_port_pool_get(struct devlink_port *devlink_port,
					  unsigned int sb_index, u16 pool_index,
					  u32 *p_threshold)
{
	struct mlxsw_core *mlxsw_core = devlink_priv(devlink_port->devlink);
	struct mlxsw_driver *mlxsw_driver = mlxsw_core->driver;
	struct mlxsw_core_port *mlxsw_core_port = __dl_port(devlink_port);

	if (!mlxsw_driver->sb_port_pool_get ||
	    !mlxsw_core_port_check(mlxsw_core_port))
		return -EOPNOTSUPP;
	return mlxsw_driver->sb_port_pool_get(mlxsw_core_port, sb_index,
					      pool_index, p_threshold);
}