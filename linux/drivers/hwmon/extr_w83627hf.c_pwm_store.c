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
struct w83627hf_data {scalar_t__ type; int* pwm; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int PWM_TO_REG (unsigned long) ; 
 int /*<<< orphan*/  W836X7HF_REG_PWM (scalar_t__,int) ; 
 struct w83627hf_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83627hf_read_value (struct w83627hf_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83627hf_write_value (struct w83627hf_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ w83627thf ; 

__attribute__((used)) static ssize_t
pwm_store(struct device *dev, struct device_attribute *devattr,
	  const char *buf, size_t count)
{
	int nr = to_sensor_dev_attr(devattr)->index;
	struct w83627hf_data *data = dev_get_drvdata(dev);
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	if (data->type == w83627thf) {
		/* bits 0-3 are reserved  in 627THF */
		data->pwm[nr] = PWM_TO_REG(val) & 0xf0;
		w83627hf_write_value(data,
				     W836X7HF_REG_PWM(data->type, nr),
				     data->pwm[nr] |
				     (w83627hf_read_value(data,
				     W836X7HF_REG_PWM(data->type, nr)) & 0x0f));
	} else {
		data->pwm[nr] = PWM_TO_REG(val);
		w83627hf_write_value(data,
				     W836X7HF_REG_PWM(data->type, nr),
				     data->pwm[nr]);
	}

	mutex_unlock(&data->update_lock);
	return count;
}