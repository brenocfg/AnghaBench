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
struct emc2103_data {scalar_t__ fan_rpm_control; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct emc2103_data* emc2103_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
pwm1_enable_show(struct device *dev, struct device_attribute *da, char *buf)
{
	struct emc2103_data *data = emc2103_update_device(dev);
	return sprintf(buf, "%d\n", data->fan_rpm_control ? 3 : 0);
}