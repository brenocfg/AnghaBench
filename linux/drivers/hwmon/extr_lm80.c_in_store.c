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
struct lm80_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ ** in; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_TO_REG (long) ; 
 int /*<<< orphan*/  LM80_REG_IN_MAX (int) ; 
 int /*<<< orphan*/  LM80_REG_IN_MIN (int) ; 
 struct lm80_data* dev_get_drvdata (struct device*) ; 
 int i_min ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  lm80_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t in_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct lm80_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int index = to_sensor_dev_attr_2(attr)->index;
	int nr = to_sensor_dev_attr_2(attr)->nr;
	long val;
	u8 reg;
	int err = kstrtol(buf, 10, &val);
	if (err < 0)
		return err;

	reg = nr == i_min ? LM80_REG_IN_MIN(index) : LM80_REG_IN_MAX(index);

	mutex_lock(&data->update_lock);
	data->in[nr][index] = IN_TO_REG(val);
	lm80_write_value(client, reg, data->in[nr][index]);
	mutex_unlock(&data->update_lock);
	return count;
}