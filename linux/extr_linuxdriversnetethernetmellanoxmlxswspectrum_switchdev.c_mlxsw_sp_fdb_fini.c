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
struct mlxsw_sp {TYPE_2__* bridge; } ;
struct TYPE_3__ {int /*<<< orphan*/  dw; } ;
struct TYPE_4__ {TYPE_1__ fdb_notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_notifier ; 
 int /*<<< orphan*/  unregister_switchdev_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_fdb_fini(struct mlxsw_sp *mlxsw_sp)
{
	cancel_delayed_work_sync(&mlxsw_sp->bridge->fdb_notify.dw);
	unregister_switchdev_notifier(&mlxsw_sp_switchdev_notifier);

}