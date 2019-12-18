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
struct led_netdev_data {char* device_name; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct led_netdev_data* led_trigger_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t device_name_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);
	ssize_t len;

	spin_lock_bh(&trigger_data->lock);
	len = sprintf(buf, "%s\n", trigger_data->device_name);
	spin_unlock_bh(&trigger_data->lock);

	return len;
}