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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7462_data {struct i2c_client* client; } ;
typedef  long ssize_t ;

/* Variables and functions */
 long EINVAL ; 
 long cvt_auto_temp (long) ; 
 struct adt7462_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  set_pwm_channel (struct i2c_client*,struct adt7462_data*,int /*<<< orphan*/ ,long) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t pwm_auto_temp_store(struct device *dev,
				   struct device_attribute *devattr,
				   const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct adt7462_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long temp;

	if (kstrtol(buf, 10, &temp))
		return -EINVAL;

	temp = cvt_auto_temp(temp);
	if (temp < 0)
		return temp;

	set_pwm_channel(client, data, attr->index, temp);

	return count;
}