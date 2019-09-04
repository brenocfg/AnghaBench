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
struct mlxsw_sp {TYPE_2__* router; } ;
struct TYPE_3__ {unsigned long interval; int /*<<< orphan*/  dw; } ;
struct TYPE_4__ {TYPE_1__ neighs_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_core_schedule_dw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 

__attribute__((used)) static void
mlxsw_sp_router_neighs_update_work_schedule(struct mlxsw_sp *mlxsw_sp)
{
	unsigned long interval = mlxsw_sp->router->neighs_update.interval;

	mlxsw_core_schedule_dw(&mlxsw_sp->router->neighs_update.dw,
			       msecs_to_jiffies(interval));
}