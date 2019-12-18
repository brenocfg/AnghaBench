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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  port_nb ; 
 int /*<<< orphan*/  port_switchdev_blocking_nb ; 
 int /*<<< orphan*/  port_switchdev_nb ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int register_switchdev_blocking_notifier (int /*<<< orphan*/ *) ; 
 int register_switchdev_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_switchdev_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ethsw_register_notifier(struct device *dev)
{
	int err;

	err = register_netdevice_notifier(&port_nb);
	if (err) {
		dev_err(dev, "Failed to register netdev notifier\n");
		return err;
	}

	err = register_switchdev_notifier(&port_switchdev_nb);
	if (err) {
		dev_err(dev, "Failed to register switchdev notifier\n");
		goto err_switchdev_nb;
	}

	err = register_switchdev_blocking_notifier(&port_switchdev_blocking_nb);
	if (err) {
		dev_err(dev, "Failed to register switchdev blocking notifier\n");
		goto err_switchdev_blocking_nb;
	}

	return 0;

err_switchdev_blocking_nb:
	unregister_switchdev_notifier(&port_switchdev_nb);
err_switchdev_nb:
	unregister_netdevice_notifier(&port_nb);
	return err;
}