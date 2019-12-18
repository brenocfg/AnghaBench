#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp {TYPE_2__* bus_info; TYPE_1__* router; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_router_fib_flush (struct mlxsw_sp*) ; 
 int mlxsw_sp_router_set_abort_trap (struct mlxsw_sp*) ; 

__attribute__((used)) static void mlxsw_sp_router_fib_abort(struct mlxsw_sp *mlxsw_sp)
{
	int err;

	if (mlxsw_sp->router->aborted)
		return;
	dev_warn(mlxsw_sp->bus_info->dev, "FIB abort triggered. Note that FIB entries are no longer being offloaded to this device.\n");
	mlxsw_sp_router_fib_flush(mlxsw_sp);
	mlxsw_sp->router->aborted = true;
	err = mlxsw_sp_router_set_abort_trap(mlxsw_sp);
	if (err)
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to set abort trap.\n");
}