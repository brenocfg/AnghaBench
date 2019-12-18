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
struct thermal_zone_device {TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* set_mode ) (struct thermal_zone_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  THERMAL_DEVICE_DISABLED ; 
 int /*<<< orphan*/  THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int stub1 (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 
 int stub2 (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 
 struct thermal_zone_device* to_thermal_zone (struct device*) ; 

__attribute__((used)) static ssize_t
mode_store(struct device *dev, struct device_attribute *attr,
	   const char *buf, size_t count)
{
	struct thermal_zone_device *tz = to_thermal_zone(dev);
	int result;

	if (!tz->ops->set_mode)
		return -EPERM;

	if (!strncmp(buf, "enabled", sizeof("enabled") - 1))
		result = tz->ops->set_mode(tz, THERMAL_DEVICE_ENABLED);
	else if (!strncmp(buf, "disabled", sizeof("disabled") - 1))
		result = tz->ops->set_mode(tz, THERMAL_DEVICE_DISABLED);
	else
		result = -EINVAL;

	if (result)
		return result;

	return count;
}