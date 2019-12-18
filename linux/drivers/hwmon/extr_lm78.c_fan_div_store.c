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
struct sensor_device_attribute {int index; } ;
struct lm78_data {int* fan_min; int* fan_div; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int) ; 
 int EINVAL ; 
 unsigned long FAN_FROM_REG (int,int /*<<< orphan*/ ) ; 
 int FAN_TO_REG (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM78_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  LM78_REG_VID_FANDIV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned long) ; 
 struct lm78_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int lm78_read_value (struct lm78_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm78_write_value (struct lm78_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t fan_div_store(struct device *dev, struct device_attribute *da,
			     const char *buf, size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct lm78_data *data = dev_get_drvdata(dev);
	int nr = attr->index;
	unsigned long min;
	u8 reg;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	min = FAN_FROM_REG(data->fan_min[nr],
			   DIV_FROM_REG(data->fan_div[nr]));

	switch (val) {
	case 1:
		data->fan_div[nr] = 0;
		break;
	case 2:
		data->fan_div[nr] = 1;
		break;
	case 4:
		data->fan_div[nr] = 2;
		break;
	case 8:
		data->fan_div[nr] = 3;
		break;
	default:
		dev_err(dev,
			"fan_div value %ld not supported. Choose one of 1, 2, 4 or 8!\n",
			val);
		mutex_unlock(&data->update_lock);
		return -EINVAL;
	}

	reg = lm78_read_value(data, LM78_REG_VID_FANDIV);
	switch (nr) {
	case 0:
		reg = (reg & 0xcf) | (data->fan_div[nr] << 4);
		break;
	case 1:
		reg = (reg & 0x3f) | (data->fan_div[nr] << 6);
		break;
	}
	lm78_write_value(data, LM78_REG_VID_FANDIV, reg);

	data->fan_min[nr] =
		FAN_TO_REG(min, DIV_FROM_REG(data->fan_div[nr]));
	lm78_write_value(data, LM78_REG_FAN_MIN(nr), data->fan_min[nr]);
	mutex_unlock(&data->update_lock);

	return count;
}