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
struct w83627hf_data {int* fan_min; int* fan_div; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int) ; 
 int DIV_TO_REG (unsigned long) ; 
 unsigned long FAN_FROM_REG (int,int /*<<< orphan*/ ) ; 
 int FAN_TO_REG (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W83627HF_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  W83781D_REG_PIN ; 
 int /*<<< orphan*/  W83781D_REG_VBAT ; 
 int /*<<< orphan*/  W83781D_REG_VID_FANDIV ; 
 struct w83627hf_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83627hf_read_value (struct w83627hf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627hf_write_value (struct w83627hf_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
fan_div_store(struct device *dev, struct device_attribute *devattr,
	      const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(devattr)->index;
	struct w83627hf_data *data = dev_get_drvdata(dev);
	unsigned long min;
	u8 reg;
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	/* Save fan_min */
	min = FAN_FROM_REG(data->fan_min[nr],
			   DIV_FROM_REG(data->fan_div[nr]));

	data->fan_div[nr] = DIV_TO_REG(val);

	reg = (w83627hf_read_value(data, nr==2 ? W83781D_REG_PIN : W83781D_REG_VID_FANDIV)
	       & (nr==0 ? 0xcf : 0x3f))
	    | ((data->fan_div[nr] & 0x03) << (nr==0 ? 4 : 6));
	w83627hf_write_value(data, nr==2 ? W83781D_REG_PIN : W83781D_REG_VID_FANDIV, reg);

	reg = (w83627hf_read_value(data, W83781D_REG_VBAT)
	       & ~(1 << (5 + nr)))
	    | ((data->fan_div[nr] & 0x04) << (3 + nr));
	w83627hf_write_value(data, W83781D_REG_VBAT, reg);

	/* Restore fan_min */
	data->fan_min[nr] = FAN_TO_REG(min, DIV_FROM_REG(data->fan_div[nr]));
	w83627hf_write_value(data, W83627HF_REG_FAN_MIN(nr), data->fan_min[nr]);

	mutex_unlock(&data->update_lock);
	return count;
}