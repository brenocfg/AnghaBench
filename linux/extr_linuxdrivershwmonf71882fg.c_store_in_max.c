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
struct f71882fg_data {scalar_t__ type; long in1_max; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  F71882FG_REG_IN1_HIGH ; 
 int /*<<< orphan*/  F81866_REG_IN1_HIGH ; 
 long clamp_val (long,int /*<<< orphan*/ ,int) ; 
 struct f71882fg_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  f71882fg_write8 (struct f71882fg_data*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ f81866a ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_in_max(struct device *dev, struct device_attribute
	*devattr, const char *buf, size_t count)
{
	struct f71882fg_data *data = dev_get_drvdata(dev);
	int err;
	long val;

	err = kstrtol(buf, 10, &val);
	if (err)
		return err;

	val /= 8;
	val = clamp_val(val, 0, 255);

	mutex_lock(&data->update_lock);
	if (data->type == f81866a)
		f71882fg_write8(data, F81866_REG_IN1_HIGH, val);
	else
		f71882fg_write8(data, F71882FG_REG_IN1_HIGH, val);
	data->in1_max = val;
	mutex_unlock(&data->update_lock);

	return count;
}