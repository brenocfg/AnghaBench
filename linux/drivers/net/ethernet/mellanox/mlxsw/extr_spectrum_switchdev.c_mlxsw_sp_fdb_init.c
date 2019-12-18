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
struct TYPE_4__ {int /*<<< orphan*/  interval; int /*<<< orphan*/  dw; } ;
struct mlxsw_sp_bridge {TYPE_2__ fdb_notify; } ;
struct mlxsw_sp {TYPE_1__* bus_info; struct mlxsw_sp_bridge* bridge; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP_DEFAULT_AGEING_TIME ; 
 int /*<<< orphan*/  MLXSW_SP_DEFAULT_LEARNING_INTERVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp_ageing_set (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fdb_notify_work ; 
 int /*<<< orphan*/  mlxsw_sp_fdb_notify_work_schedule (struct mlxsw_sp*) ; 
 struct notifier_block mlxsw_sp_switchdev_blocking_notifier ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_notifier ; 
 int register_switchdev_blocking_notifier (struct notifier_block*) ; 
 int register_switchdev_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_switchdev_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_fdb_init(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_bridge *bridge = mlxsw_sp->bridge;
	struct notifier_block *nb;
	int err;

	err = mlxsw_sp_ageing_set(mlxsw_sp, MLXSW_SP_DEFAULT_AGEING_TIME);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to set default ageing time\n");
		return err;
	}

	err = register_switchdev_notifier(&mlxsw_sp_switchdev_notifier);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to register switchdev notifier\n");
		return err;
	}

	nb = &mlxsw_sp_switchdev_blocking_notifier;
	err = register_switchdev_blocking_notifier(nb);
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to register switchdev blocking notifier\n");
		goto err_register_switchdev_blocking_notifier;
	}

	INIT_DELAYED_WORK(&bridge->fdb_notify.dw, mlxsw_sp_fdb_notify_work);
	bridge->fdb_notify.interval = MLXSW_SP_DEFAULT_LEARNING_INTERVAL;
	mlxsw_sp_fdb_notify_work_schedule(mlxsw_sp);
	return 0;

err_register_switchdev_blocking_notifier:
	unregister_switchdev_notifier(&mlxsw_sp_switchdev_notifier);
	return err;
}