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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct gl520_data {int* fan_div; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GL520_REG_FAN_DIV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long) ; 
 struct gl520_data* dev_get_drvdata (struct device*) ; 
 int gl520_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl520_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_div_store(struct device *dev,
			     struct device_attribute *attr, const char *buf,
			     size_t count)
{
	struct gl520_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int n = to_sensor_dev_attr(attr)->index;
	u8 r;
	unsigned long v;
	int err;

	err = kstrtoul(buf, 10, &v);
	if (err)
		return err;

	switch (v) {
	case 1:
		r = 0;
		break;
	case 2:
		r = 1;
		break;
	case 4:
		r = 2;
		break;
	case 8:
		r = 3;
		break;
	default:
		dev_err(&client->dev,
	"fan_div value %ld not supported. Choose one of 1, 2, 4 or 8!\n", v);
		return -EINVAL;
	}

	mutex_lock(&data->update_lock);
	data->fan_div[n] = r;

	if (n == 0)
		gl520_write_value(client, GL520_REG_FAN_DIV,
				  (gl520_read_value(client, GL520_REG_FAN_DIV)
				   & ~0xc0) | (r << 6));
	else
		gl520_write_value(client, GL520_REG_FAN_DIV,
				  (gl520_read_value(client, GL520_REG_FAN_DIV)
				   & ~0x30) | (r << 4));

	mutex_unlock(&data->update_lock);
	return count;
}