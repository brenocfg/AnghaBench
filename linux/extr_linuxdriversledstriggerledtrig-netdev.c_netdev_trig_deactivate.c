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
struct led_netdev_data {scalar_t__ net_dev; int /*<<< orphan*/  work; int /*<<< orphan*/  notifier; } ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct led_netdev_data*) ; 
 struct led_netdev_data* led_get_trigger_data (struct led_classdev*) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netdev_trig_deactivate(struct led_classdev *led_cdev)
{
	struct led_netdev_data *trigger_data = led_get_trigger_data(led_cdev);

	unregister_netdevice_notifier(&trigger_data->notifier);

	cancel_delayed_work_sync(&trigger_data->work);

	if (trigger_data->net_dev)
		dev_put(trigger_data->net_dev);

	kfree(trigger_data);
}