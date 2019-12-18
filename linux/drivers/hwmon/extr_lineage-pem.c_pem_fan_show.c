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
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct pem_data {int /*<<< orphan*/  fan_speed; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pem_data*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTR_ERR (struct pem_data*) ; 
 long pem_get_fan (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct pem_data* pem_update_device (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,long) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pem_fan_show(struct device *dev, struct device_attribute *da,
			    char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct pem_data *data = pem_update_device(dev);
	long value;

	if (IS_ERR(data))
		return PTR_ERR(data);

	value = pem_get_fan(data->fan_speed, sizeof(data->fan_speed),
			    attr->index);

	return snprintf(buf, PAGE_SIZE, "%ld\n", value);
}