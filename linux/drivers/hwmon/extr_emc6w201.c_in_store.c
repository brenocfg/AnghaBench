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
struct emc6w201_data {long** in; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; int nr; } ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (long,int) ; 
 int /*<<< orphan*/  EMC6W201_REG_IN_HIGH (int) ; 
 int /*<<< orphan*/  EMC6W201_REG_IN_LOW (int) ; 
 long clamp_val (long,int /*<<< orphan*/ ,int) ; 
 struct emc6w201_data* dev_get_drvdata (struct device*) ; 
 int emc6w201_write8 (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 int kstrtol (char const*,int,long*) ; 
 int min ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* nominal_mv ; 
 TYPE_1__* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t in_store(struct device *dev, struct device_attribute *devattr,
			const char *buf, size_t count)
{
	struct emc6w201_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int sf = to_sensor_dev_attr_2(devattr)->index;
	int nr = to_sensor_dev_attr_2(devattr)->nr;
	int err;
	long val;
	u8 reg;

	err = kstrtol(buf, 10, &val);
	if (err < 0)
		return err;

	val = clamp_val(val, 0, 255 * nominal_mv[nr] / 192);
	val = DIV_ROUND_CLOSEST(val * 192, nominal_mv[nr]);
	reg = (sf == min) ? EMC6W201_REG_IN_LOW(nr)
			  : EMC6W201_REG_IN_HIGH(nr);

	mutex_lock(&data->update_lock);
	data->in[sf][nr] = val;
	err = emc6w201_write8(client, reg, data->in[sf][nr]);
	mutex_unlock(&data->update_lock);

	return err < 0 ? err : count;
}