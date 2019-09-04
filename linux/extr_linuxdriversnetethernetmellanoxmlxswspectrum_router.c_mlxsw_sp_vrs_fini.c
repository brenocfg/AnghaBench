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
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {int /*<<< orphan*/  vrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_flush_owq () ; 
 int /*<<< orphan*/  mlxsw_sp_router_fib_flush (struct mlxsw_sp*) ; 

__attribute__((used)) static void mlxsw_sp_vrs_fini(struct mlxsw_sp *mlxsw_sp)
{
	/* At this stage we're guaranteed not to have new incoming
	 * FIB notifications and the work queue is free from FIBs
	 * sitting on top of mlxsw netdevs. However, we can still
	 * have other FIBs queued. Flush the queue before flushing
	 * the device's tables. No need for locks, as we're the only
	 * writer.
	 */
	mlxsw_core_flush_owq();
	mlxsw_sp_router_fib_flush(mlxsw_sp);
	kfree(mlxsw_sp->router->vrs);
}