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
struct apds990x_chip {int /*<<< orphan*/  mutex; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int apds990x_set_arate (struct apds990x_chip*,unsigned long) ; 
 struct apds990x_chip* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t apds990x_rate_store(struct device *dev,
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
	ret = apds990x_set_arate(chip, value);
	mutex_unlock(&chip->mutex);

	if (ret < 0)
		return ret;
	return len;
}