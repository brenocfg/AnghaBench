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
struct max6650_data {int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct max6650_data* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int max6650_set_target (struct max6650_data*,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t fan1_target_store(struct device *dev,
				 struct device_attribute *devattr,
				 const char *buf, size_t count)
{
	struct max6650_data *data = dev_get_drvdata(dev);
	unsigned long rpm;
	int err;

	err = kstrtoul(buf, 10, &rpm);
	if (err)
		return err;

	mutex_lock(&data->update_lock);

	err = max6650_set_target(data, rpm);

	mutex_unlock(&data->update_lock);

	if (err < 0)
		return err;

	return count;
}