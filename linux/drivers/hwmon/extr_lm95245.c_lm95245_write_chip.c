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
typedef  int u32 ;
struct lm95245_data {int /*<<< orphan*/  update_lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct lm95245_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_chip_update_interval 128 
 int lm95245_set_conversion_rate (struct lm95245_data*,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm95245_write_chip(struct device *dev, u32 attr, int channel,
			      long val)
{
	struct lm95245_data *data = dev_get_drvdata(dev);
	int ret;

	switch (attr) {
	case hwmon_chip_update_interval:
		mutex_lock(&data->update_lock);
		ret = lm95245_set_conversion_rate(data, val);
		mutex_unlock(&data->update_lock);
		return ret;
	default:
		return -EOPNOTSUPP;
	}
}