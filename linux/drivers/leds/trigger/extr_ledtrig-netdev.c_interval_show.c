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
struct led_netdev_data {int /*<<< orphan*/  interval; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 struct led_netdev_data* led_trigger_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t interval_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct led_netdev_data *trigger_data = led_trigger_get_drvdata(dev);

	return sprintf(buf, "%u\n",
		       jiffies_to_msecs(atomic_read(&trigger_data->interval)));
}