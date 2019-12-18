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
typedef  int /*<<< orphan*/  u16 ;
struct w83627hf_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp_max; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM75_TEMP_TO_REG (long) ; 
 int /*<<< orphan*/  TEMP_TO_REG (long) ; 
 struct w83627hf_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int /*<<< orphan*/ * w83627hf_reg_temp_over ; 
 int /*<<< orphan*/  w83627hf_write_value (struct w83627hf_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
temp_max_store(struct device *dev, struct device_attribute *devattr,
	       const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(devattr)->index;
	struct w83627hf_data *data = dev_get_drvdata(dev);
	u16 tmp;
	long val;
	int err;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	tmp = (nr) ? LM75_TEMP_TO_REG(val) : TEMP_TO_REG(val);
	mutex_lock(&data->update_lock);
	data->temp_max[nr] = tmp;
	w83627hf_write_value(data, w83627hf_reg_temp_over[nr], tmp);
	mutex_unlock(&data->update_lock);
	return count;
}