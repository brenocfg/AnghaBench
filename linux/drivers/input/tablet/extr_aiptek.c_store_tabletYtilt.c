#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int yTilt; } ;
struct aiptek {TYPE_1__ newSetting; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int AIPTEK_TILT_DISABLE ; 
 int AIPTEK_TILT_MAX ; 
 int AIPTEK_TILT_MIN ; 
 size_t EINVAL ; 
 struct aiptek* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtoint (char const*,int,int*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static ssize_t
store_tabletYtilt(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);
	int y;

	if (kstrtoint(buf, 10, &y)) {
		size_t len = buf[count - 1] == '\n' ? count - 1 : count;

		if (strncmp(buf, "disable", len))
			return -EINVAL;

		aiptek->newSetting.yTilt = AIPTEK_TILT_DISABLE;
	} else {
		if (y < AIPTEK_TILT_MIN || y > AIPTEK_TILT_MAX)
			return -EINVAL;

		aiptek->newSetting.yTilt = y;
	}

	return count;
}