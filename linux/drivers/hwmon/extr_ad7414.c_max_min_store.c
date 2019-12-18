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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7414_data {long* temps; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/ * AD7414_REG_LIMIT ; 
 int /*<<< orphan*/  ad7414_write (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 long clamp_val (long,int,int) ; 
 struct ad7414_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t max_min_store(struct device *dev,
			     struct device_attribute *attr, const char *buf,
			     size_t count)
{
	struct ad7414_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int index = to_sensor_dev_attr(attr)->index;
	u8 reg = AD7414_REG_LIMIT[index];
	long temp;
	int ret = kstrtol(buf, 10, &temp);

	if (ret < 0)
		return ret;

	temp = clamp_val(temp, -40000, 85000);
	temp = (temp + (temp < 0 ? -500 : 500)) / 1000;

	mutex_lock(&data->lock);
	data->temps[index] = temp;
	ad7414_write(client, reg, temp);
	mutex_unlock(&data->lock);
	return count;
}