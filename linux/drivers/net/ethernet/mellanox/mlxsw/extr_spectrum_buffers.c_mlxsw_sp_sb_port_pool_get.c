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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_sb_pm {int /*<<< orphan*/  max_buff; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_core_port {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_port* mlxsw_core_port_driver_priv (struct mlxsw_core_port*) ; 
 struct mlxsw_sp_sb_pm* mlxsw_sp_sb_pm_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_sb_threshold_out (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_sp_sb_port_pool_get(struct mlxsw_core_port *mlxsw_core_port,
			      unsigned int sb_index, u16 pool_index,
			      u32 *p_threshold)
{
	struct mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	struct mlxsw_sp_sb_pm *pm = mlxsw_sp_sb_pm_get(mlxsw_sp, local_port,
						       pool_index);

	*p_threshold = mlxsw_sp_sb_threshold_out(mlxsw_sp, pool_index,
						 pm->max_buff);
	return 0;
}