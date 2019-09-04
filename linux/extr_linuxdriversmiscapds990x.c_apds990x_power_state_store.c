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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct apds990x_chip {int lux_wait_fresh_res; int /*<<< orphan*/  mutex; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  apds990x_force_a_refresh (struct apds990x_chip*) ; 
 int /*<<< orphan*/  apds990x_force_p_refresh (struct apds990x_chip*) ; 
 struct apds990x_chip* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_suspended (struct device*) ; 

__attribute__((used)) static ssize_t apds990x_power_state_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len)
{
	struct apds990x_chip *chip =  dev_get_drvdata(dev);
	unsigned long value;
	int ret;

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		return ret;

	if (value) {
		pm_runtime_get_sync(dev);
		mutex_lock(&chip->mutex);
		chip->lux_wait_fresh_res = true;
		apds990x_force_a_refresh(chip);
		apds990x_force_p_refresh(chip);
		mutex_unlock(&chip->mutex);
	} else {
		if (!pm_runtime_suspended(dev))
			pm_runtime_put(dev);
	}
	return len;
}