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
struct TYPE_2__ {int /*<<< orphan*/  interval; int /*<<< orphan*/  dw; } ;
struct mlxsw_sp_bridge {TYPE_1__ fdb_notify; } ;
struct mlxsw_sp {struct mlxsw_sp_bridge* bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_core_schedule_dw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_fdb_notify_work_schedule(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_bridge *bridge = mlxsw_sp->bridge;

	mlxsw_core_schedule_dw(&bridge->fdb_notify.dw,
			       msecs_to_jiffies(bridge->fdb_notify.interval));
}