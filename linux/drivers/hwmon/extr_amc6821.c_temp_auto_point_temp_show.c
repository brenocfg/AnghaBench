#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct amc6821_data {int* temp1_auto_point_temp; int* temp2_auto_point_temp; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct amc6821_data* amc6821_update_device (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_auto_point_temp_show(struct device *dev,
					 struct device_attribute *devattr,
					 char *buf)
{
	int ix = to_sensor_dev_attr_2(devattr)->index;
	int nr = to_sensor_dev_attr_2(devattr)->nr;
	struct amc6821_data *data = amc6821_update_device(dev);
	switch (nr) {
	case 1:
		return sprintf(buf, "%d\n",
			data->temp1_auto_point_temp[ix] * 1000);
	case 2:
		return sprintf(buf, "%d\n",
			data->temp2_auto_point_temp[ix] * 1000);
	default:
		dev_dbg(dev, "Unknown attr->nr (%d).\n", nr);
		return -EINVAL;
	}
}