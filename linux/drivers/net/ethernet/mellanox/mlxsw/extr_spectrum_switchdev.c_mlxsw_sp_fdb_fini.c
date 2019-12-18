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
struct notifier_block {int dummy; } ;
struct mlxsw_sp {TYPE_2__* bridge; } ;
struct TYPE_3__ {int /*<<< orphan*/  dw; } ;
struct TYPE_4__ {TYPE_1__ fdb_notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct notifier_block mlxsw_sp_switchdev_blocking_notifier ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_notifier ; 
 int /*<<< orphan*/  unregister_switchdev_blocking_notifier (struct notifier_block*) ; 
 int /*<<< orphan*/  unregister_switchdev_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_fdb_fini(struct mlxsw_sp *mlxsw_sp)
{
	struct notifier_block *nb;

	cancel_delayed_work_sync(&mlxsw_sp->bridge->fdb_notify.dw);

	nb = &mlxsw_sp_switchdev_blocking_notifier;
	unregister_switchdev_blocking_notifier(nb);

	unregister_switchdev_notifier(&mlxsw_sp_switchdev_notifier);
}