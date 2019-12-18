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
struct it87_data {int /*<<< orphan*/  update_lock; scalar_t__ valid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int BIT (int) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  IT87_REG_CONFIG ; 
 struct it87_data* dev_get_drvdata (struct device*) ; 
 int it87_read_value (struct it87_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  it87_write_value (struct it87_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t clear_intrusion(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t count)
{
	struct it87_data *data = dev_get_drvdata(dev);
	int config;
	long val;

	if (kstrtol(buf, 10, &val) < 0 || val != 0)
		return -EINVAL;

	mutex_lock(&data->update_lock);
	config = it87_read_value(data, IT87_REG_CONFIG);
	if (config < 0) {
		count = config;
	} else {
		config |= BIT(5);
		it87_write_value(data, IT87_REG_CONFIG, config);
		/* Invalidate cache to force re-read */
		data->valid = 0;
	}
	mutex_unlock(&data->update_lock);

	return count;
}