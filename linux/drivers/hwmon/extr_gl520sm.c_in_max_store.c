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
struct i2c_client {int dummy; } ;
struct gl520_data {int* in_max; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/ * GL520_REG_IN_MAX ; 
 int IN_TO_REG (long) ; 
 int VDD_TO_REG (long) ; 
 struct gl520_data* dev_get_drvdata (struct device*) ; 
 int gl520_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl520_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t in_max_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct gl520_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int n = to_sensor_dev_attr(attr)->index;
	u8 r;
	long v;
	int err;

	err = kstrtol(buf, 10, &v);
	if (err)
		return err;

	if (n == 0)
		r = VDD_TO_REG(v);
	else
		r = IN_TO_REG(v);

	mutex_lock(&data->update_lock);

	data->in_max[n] = r;

	if (n < 4)
		gl520_write_value(client, GL520_REG_IN_MAX[n],
				  (gl520_read_value(client, GL520_REG_IN_MAX[n])
				   & ~0xff00) | (r << 8));
	else
		gl520_write_value(client, GL520_REG_IN_MAX[n], r);

	mutex_unlock(&data->update_lock);
	return count;
}