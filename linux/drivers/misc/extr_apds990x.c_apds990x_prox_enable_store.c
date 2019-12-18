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
struct apds990x_chip {scalar_t__ prox_en; int /*<<< orphan*/  mutex; scalar_t__ prox_data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  apds990x_mode_on (struct apds990x_chip*) ; 
 struct apds990x_chip* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspended (struct device*) ; 

__attribute__((used)) static ssize_t apds990x_prox_enable_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len)
{
	struct apds990x_chip *chip =  dev_get_drvdata(dev);
	unsigned long value;
	int ret;

	ret = kstrtoul(buf, 0, &value);
	if (ret)
		return ret;

	mutex_lock(&chip->mutex);

	if (!chip->prox_en)
		chip->prox_data = 0;

	if (value)
		chip->prox_en++;
	else if (chip->prox_en > 0)
		chip->prox_en--;

	if (!pm_runtime_suspended(dev))
		apds990x_mode_on(chip);
	mutex_unlock(&chip->mutex);
	return len;
}