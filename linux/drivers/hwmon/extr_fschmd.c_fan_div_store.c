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
struct fschmd_data {size_t kind; int* fan_ripple; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ ** FSCHMD_REG_FAN_RIPPLE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long) ; 
 struct fschmd_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_div_store(struct device *dev,
			     struct device_attribute *devattr,
			     const char *buf, size_t count)
{
	u8 reg;
	int index = to_sensor_dev_attr(devattr)->index;
	struct fschmd_data *data = dev_get_drvdata(dev);
	/* supported values: 2, 4, 8 */
	unsigned long v;
	int err;

	err = kstrtoul(buf, 10, &v);
	if (err)
		return err;

	switch (v) {
	case 2:
		v = 1;
		break;
	case 4:
		v = 2;
		break;
	case 8:
		v = 3;
		break;
	default:
		dev_err(dev,
			"fan_div value %lu not supported. Choose one of 2, 4 or 8!\n",
			v);
		return -EINVAL;
	}

	mutex_lock(&data->update_lock);

	reg = i2c_smbus_read_byte_data(to_i2c_client(dev),
		FSCHMD_REG_FAN_RIPPLE[data->kind][index]);

	/* bits 2..7 reserved => mask with 0x03 */
	reg &= ~0x03;
	reg |= v;

	i2c_smbus_write_byte_data(to_i2c_client(dev),
		FSCHMD_REG_FAN_RIPPLE[data->kind][index], reg);

	data->fan_ripple[index] = reg;

	mutex_unlock(&data->update_lock);

	return count;
}