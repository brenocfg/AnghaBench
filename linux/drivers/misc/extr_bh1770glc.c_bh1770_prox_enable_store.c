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
struct bh1770_chip {scalar_t__ prox_enable_count; int /*<<< orphan*/  mutex; scalar_t__ prox_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  bh1770_prox_mode_control (struct bh1770_chip*) ; 
 struct bh1770_chip* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspended (struct device*) ; 

__attribute__((used)) static ssize_t bh1770_prox_enable_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct bh1770_chip *chip =  dev_get_drvdata(dev);
	unsigned long value;
	int ret;

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		return ret;

	mutex_lock(&chip->mutex);
	/* Assume no proximity. Sensor will tell real state soon */
	if (!chip->prox_enable_count)
		chip->prox_data = 0;

	if (value)
		chip->prox_enable_count++;
	else if (chip->prox_enable_count > 0)
		chip->prox_enable_count--;
	else
		goto leave;

	/* Run control only when chip is powered on */
	if (!pm_runtime_suspended(dev))
		bh1770_prox_mode_control(chip);
leave:
	mutex_unlock(&chip->mutex);
	return count;
}