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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ads1015_read_adc (struct i2c_client*,int) ; 
 int ads1015_reg_to_mv (struct i2c_client*,int,int) ; 
 int sprintf (char*,char*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_in(struct device *dev, struct device_attribute *da,
	char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct i2c_client *client = to_i2c_client(dev);
	int res;
	int index = attr->index;

	res = ads1015_read_adc(client, index);
	if (res < 0)
		return res;

	return sprintf(buf, "%d\n", ads1015_reg_to_mv(client, index, res));
}