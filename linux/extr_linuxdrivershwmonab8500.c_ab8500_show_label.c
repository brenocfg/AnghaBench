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
struct sensor_device_attribute {int index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ab8500_show_label(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	char *label;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	int index = attr->index;

	switch (index) {
	case 1:
		label = "ext_adc1";
		break;
	case 2:
		label = "ext_adc2";
		break;
	case 3:
		label = "bat_temp";
		break;
	case 4:
		label = "bat_ctrl";
		break;
	default:
		return -EINVAL;
	}

	return sprintf(buf, "%s\n", label);
}