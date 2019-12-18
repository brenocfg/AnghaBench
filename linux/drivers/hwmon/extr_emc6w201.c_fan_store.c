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
struct i2c_client {int dummy; } ;
struct emc6w201_data {unsigned long** fan; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  EMC6W201_REG_FAN_MIN (int) ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct emc6w201_data* dev_get_drvdata (struct device*) ; 
 int emc6w201_write16 (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_store(struct device *dev, struct device_attribute *devattr,
			 const char *buf, size_t count)
{
	struct emc6w201_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int sf = to_sensor_dev_attr_2(devattr)->index;
	int nr = to_sensor_dev_attr_2(devattr)->nr;
	int err;
	unsigned long val;

	err = kstrtoul(buf, 10, &val);
	if (err < 0)
		return err;

	if (val == 0) {
		val = 0xFFFF;
	} else {
		val = DIV_ROUND_CLOSEST(5400000U, val);
		val = clamp_val(val, 0, 0xFFFE);
	}

	mutex_lock(&data->update_lock);
	data->fan[sf][nr] = val;
	err = emc6w201_write16(client, EMC6W201_REG_FAN_MIN(nr),
			       data->fan[sf][nr]);
	mutex_unlock(&data->update_lock);

	return err < 0 ? err : count;
}