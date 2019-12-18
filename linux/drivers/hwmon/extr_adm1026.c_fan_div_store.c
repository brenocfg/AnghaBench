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
struct adm1026_data {int* fan_div; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1026_REG_FAN_DIV_0_3 ; 
 int /*<<< orphan*/  ADM1026_REG_FAN_DIV_4_7 ; 
 int DIV_FROM_REG (int) ; 
 int DIV_TO_REG (long) ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct adm1026_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fixup_fan_min (struct device*,int,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_div_store(struct device *dev,
			     struct device_attribute *attr, const char *buf,
			     size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	int nr = sensor_attr->index;
	struct adm1026_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	long val;
	int orig_div, new_div;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	new_div = DIV_TO_REG(val);

	mutex_lock(&data->update_lock);
	orig_div = data->fan_div[nr];
	data->fan_div[nr] = DIV_FROM_REG(new_div);

	if (nr < 4) { /* 0 <= nr < 4 */
		adm1026_write_value(client, ADM1026_REG_FAN_DIV_0_3,
				    (DIV_TO_REG(data->fan_div[0]) << 0) |
				    (DIV_TO_REG(data->fan_div[1]) << 2) |
				    (DIV_TO_REG(data->fan_div[2]) << 4) |
				    (DIV_TO_REG(data->fan_div[3]) << 6));
	} else { /* 3 < nr < 8 */
		adm1026_write_value(client, ADM1026_REG_FAN_DIV_4_7,
				    (DIV_TO_REG(data->fan_div[4]) << 0) |
				    (DIV_TO_REG(data->fan_div[5]) << 2) |
				    (DIV_TO_REG(data->fan_div[6]) << 4) |
				    (DIV_TO_REG(data->fan_div[7]) << 6));
	}

	if (data->fan_div[nr] != orig_div)
		fixup_fan_min(dev, nr, orig_div);

	mutex_unlock(&data->update_lock);
	return count;
}