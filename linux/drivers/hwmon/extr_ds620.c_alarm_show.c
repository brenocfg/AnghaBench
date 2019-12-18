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
typedef  int u16 ;
struct sensor_device_attribute {int index; } ;
struct i2c_client {int dummy; } ;
struct ds620_data {struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS620_REG_CONF ; 
 scalar_t__ IS_ERR (struct ds620_data*) ; 
 int PTR_ERR (struct ds620_data*) ; 
 struct ds620_data* ds620_update_client (struct device*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t alarm_show(struct device *dev, struct device_attribute *da,
			  char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct ds620_data *data = ds620_update_client(dev);
	struct i2c_client *client;
	u16 conf, new_conf;
	int res;

	if (IS_ERR(data))
		return PTR_ERR(data);

	client = data->client;

	/* reset alarms if necessary */
	res = i2c_smbus_read_word_swapped(client, DS620_REG_CONF);
	if (res < 0)
		return res;

	new_conf = conf = res;
	new_conf &= ~attr->index;
	if (conf != new_conf) {
		res = i2c_smbus_write_word_swapped(client, DS620_REG_CONF,
						   new_conf);
		if (res < 0)
			return res;
	}

	return sprintf(buf, "%d\n", !!(conf & attr->index));
}