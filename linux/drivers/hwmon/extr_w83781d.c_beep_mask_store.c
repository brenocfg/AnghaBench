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
struct w83781d_data {int beep_mask; scalar_t__ type; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BEEP_MASK_TO_REG (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS1 ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS2 ; 
 int /*<<< orphan*/  W83781D_REG_BEEP_INTS3 ; 
 scalar_t__ as99127f ; 
 struct w83781d_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ w83781d ; 
 int /*<<< orphan*/  w83781d_write_value (struct w83781d_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
beep_mask_store(struct device *dev, struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct w83781d_data *data = dev_get_drvdata(dev);
	unsigned long val;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return err;

	mutex_lock(&data->update_lock);
	data->beep_mask &= 0x8000; /* preserve beep enable */
	data->beep_mask |= BEEP_MASK_TO_REG(val, data->type);
	w83781d_write_value(data, W83781D_REG_BEEP_INTS1,
			    data->beep_mask & 0xff);
	w83781d_write_value(data, W83781D_REG_BEEP_INTS2,
			    (data->beep_mask >> 8) & 0xff);
	if (data->type != w83781d && data->type != as99127f) {
		w83781d_write_value(data, W83781D_REG_BEEP_INTS3,
				    ((data->beep_mask) >> 16) & 0xff);
	}
	mutex_unlock(&data->update_lock);

	return count;
}