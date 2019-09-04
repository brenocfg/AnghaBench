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
struct w83627hf_data {int vrm_ovt; scalar_t__ type; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * in_max; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IN_TO_REG (unsigned long) ; 
 int /*<<< orphan*/  W83781D_REG_IN_MAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clamp_val (unsigned long,int /*<<< orphan*/ ,int) ; 
 struct w83627hf_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w83627hf_write_value (struct w83627hf_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ w83627thf ; 
 scalar_t__ w83637hf ; 
 scalar_t__ w83687thf ; 

__attribute__((used)) static ssize_t in0_max_store(struct device *dev,
			     struct device_attribute *attr, const char *buf,
			     size_t count)
{
	struct w83627hf_data *data = dev_get_drvdata(dev);
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	if ((data->vrm_ovt & 0x01) &&
		(w83627thf == data->type || w83637hf == data->type
		 || w83687thf == data->type))
		
		/* use VRM9 calculation */
		data->in_max[0] =
			clamp_val(((val * 100) - 70000 + 244) / 488, 0, 255);
	else
		/* use VRM8 (standard) calculation */
		data->in_max[0] = IN_TO_REG(val);

	w83627hf_write_value(data, W83781D_REG_IN_MAX(0), data->in_max[0]);
	mutex_unlock(&data->update_lock);
	return count;
}