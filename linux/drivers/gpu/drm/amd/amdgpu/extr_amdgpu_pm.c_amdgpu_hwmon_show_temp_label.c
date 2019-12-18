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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {char* label; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PP_TEMP_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_2__* temp_label ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_show_temp_label(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	int channel = to_sensor_dev_attr(attr)->index;

	if (channel >= PP_TEMP_MAX)
		return -EINVAL;

	return snprintf(buf, PAGE_SIZE, "%s\n", temp_label[channel].label);
}