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
struct led_classdev_flash {int dummy; } ;
struct led_classdev {int /*<<< orphan*/  led_access; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 size_t kstrtoul (char const*,int,unsigned long*) ; 
 struct led_classdev_flash* lcdev_to_flcdev (struct led_classdev*) ; 
 size_t led_set_flash_strobe (struct led_classdev_flash*,unsigned long) ; 
 scalar_t__ led_sysfs_is_disabled (struct led_classdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t flash_strobe_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	unsigned long state;
	ssize_t ret = -EINVAL;

	mutex_lock(&led_cdev->led_access);

	if (led_sysfs_is_disabled(led_cdev)) {
		ret = -EBUSY;
		goto unlock;
	}

	ret = kstrtoul(buf, 10, &state);
	if (ret)
		goto unlock;

	if (state > 1) {
		ret = -EINVAL;
		goto unlock;
	}

	ret = led_set_flash_strobe(fled_cdev, state);
	if (ret < 0)
		goto unlock;
	ret = size;
unlock:
	mutex_unlock(&led_cdev->led_access);
	return ret;
}