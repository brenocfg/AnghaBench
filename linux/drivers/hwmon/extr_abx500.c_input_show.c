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
typedef  int /*<<< orphan*/  u8 ;
struct sensor_device_attribute {size_t index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* read_sensor ) (struct abx500_temp*,int /*<<< orphan*/ ,int*) ;} ;
struct abx500_temp {TYPE_1__ ops; int /*<<< orphan*/ * gpadc_addr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct abx500_temp* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 
 int stub1 (struct abx500_temp*,int /*<<< orphan*/ ,int*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t input_show(struct device *dev,
			  struct device_attribute *devattr, char *buf)
{
	int ret, temp;
	struct abx500_temp *data = dev_get_drvdata(dev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	u8 gpadc_addr = data->gpadc_addr[attr->index];

	ret = data->ops.read_sensor(data, gpadc_addr, &temp);
	if (ret < 0)
		return ret;

	return sprintf(buf, "%d\n", temp);
}