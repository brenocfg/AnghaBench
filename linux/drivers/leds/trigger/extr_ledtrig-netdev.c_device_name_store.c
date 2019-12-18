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
struct led_netdev_data {char* device_name; int /*<<< orphan*/  lock; scalar_t__ last_activity; int /*<<< orphan*/  mode; int /*<<< orphan*/ * net_dev; int /*<<< orphan*/  work; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t IFNAMSIZ ; 
 int /*<<< orphan*/  NETDEV_LED_MODE_LINKUP ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 struct led_netdev_data* led_trigger_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_baseline_state (struct led_netdev_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t device_name_store(struct device *dev,
				 struct device_attribute *attr, const char *buf,
				 size_t size)
{
	struct led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);

	if (size >= IFNAMSIZ)
		return -EINVAL;

	cancel_delayed_work_sync(&trigger_data->work);

	spin_lock_bh(&trigger_data->lock);

	if (trigger_data->net_dev) {
		dev_put(trigger_data->net_dev);
		trigger_data->net_dev = NULL;
	}

	memcpy(trigger_data->device_name, buf, size);
	trigger_data->device_name[size] = 0;
	if (size > 0 && trigger_data->device_name[size - 1] == '\n')
		trigger_data->device_name[size - 1] = 0;

	if (trigger_data->device_name[0] != 0)
		trigger_data->net_dev =
		    dev_get_by_name(&init_net, trigger_data->device_name);

	clear_bit(NETDEV_LED_MODE_LINKUP, &trigger_data->mode);
	if (trigger_data->net_dev != NULL)
		if (netif_carrier_ok(trigger_data->net_dev))
			set_bit(NETDEV_LED_MODE_LINKUP, &trigger_data->mode);

	trigger_data->last_activity = 0;

	set_baseline_state(trigger_data);
	spin_unlock_bh(&trigger_data->lock);

	return size;
}