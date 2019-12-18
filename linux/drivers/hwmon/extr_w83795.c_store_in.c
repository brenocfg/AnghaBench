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
typedef  int u8 ;
struct w83795_data {int has_gain; int** in_lsb; int** in; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute_2 {int nr; int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t IN_LSB_IDX ; 
 int /*<<< orphan*/  IN_LSB_REG (int,int) ; 
 size_t IN_LSB_SHIFT ; 
 int** IN_LSB_SHIFT_IDX ; 
 int /*<<< orphan*/ ** W83795_REG_IN ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct w83795_data* i2c_get_clientdata (struct i2c_client*) ; 
 unsigned long in_to_reg (int,unsigned long) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int w83795_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83795_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
store_in(struct device *dev, struct device_attribute *attr,
	 const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	int nr = sensor_attr->nr;
	int index = sensor_attr->index;
	struct i2c_client *client = to_i2c_client(dev);
	struct w83795_data *data = i2c_get_clientdata(client);
	unsigned long val;
	u8 tmp;
	u8 lsb_idx;

	if (kstrtoul(buf, 10, &val) < 0)
		return -EINVAL;
	val = in_to_reg(index, val);

	if ((index >= 17) &&
	    !((data->has_gain >> (index - 17)) & 1))
		val /= 8;
	val = clamp_val(val, 0, 0x3FF);
	mutex_lock(&data->update_lock);

	lsb_idx = IN_LSB_SHIFT_IDX[index][IN_LSB_IDX];
	tmp = w83795_read(client, IN_LSB_REG(lsb_idx, nr));
	tmp &= ~(0x03 << IN_LSB_SHIFT_IDX[index][IN_LSB_SHIFT]);
	tmp |= (val & 0x03) << IN_LSB_SHIFT_IDX[index][IN_LSB_SHIFT];
	w83795_write(client, IN_LSB_REG(lsb_idx, nr), tmp);
	data->in_lsb[lsb_idx][nr] = tmp;

	tmp = (val >> 2) & 0xff;
	w83795_write(client, W83795_REG_IN[index][nr], tmp);
	data->in[index][nr] = tmp;

	mutex_unlock(&data->update_lock);
	return count;
}