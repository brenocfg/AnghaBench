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
struct max6697_data {long temp_offset; scalar_t__ type; long** temp; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int nr; int index; } ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (long,int) ; 
 int /*<<< orphan*/ * MAX6697_REG_CRIT ; 
 int /*<<< orphan*/ * MAX6697_REG_MAX ; 
 long clamp_val (long,int /*<<< orphan*/ ,int) ; 
 struct max6697_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int kstrtol (char const*,int,long*) ; 
 scalar_t__ max6581 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t temp_store(struct device *dev,
			  struct device_attribute *devattr, const char *buf,
			  size_t count)
{
	int nr = to_sensor_dev_attr_2(devattr)->nr;
	int index = to_sensor_dev_attr_2(devattr)->index;
	struct max6697_data *data = dev_get_drvdata(dev);
	long temp;
	int ret;

	ret = kstrtol(buf, 10, &temp);
	if (ret < 0)
		return ret;

	mutex_lock(&data->update_lock);
	temp = DIV_ROUND_CLOSEST(temp, 1000) + data->temp_offset;
	temp = clamp_val(temp, 0, data->type == max6581 ? 255 : 127);
	data->temp[nr][index] = temp;
	ret = i2c_smbus_write_byte_data(data->client,
					index == 2 ? MAX6697_REG_MAX[nr]
						   : MAX6697_REG_CRIT[nr],
					temp);
	mutex_unlock(&data->update_lock);

	return ret < 0 ? ret : count;
}