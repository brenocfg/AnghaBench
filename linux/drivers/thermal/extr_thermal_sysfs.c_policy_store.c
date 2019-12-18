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
struct thermal_zone_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int THERMAL_NAME_LENGTH ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int thermal_zone_device_set_policy (struct thermal_zone_device*,char*) ; 
 struct thermal_zone_device* to_thermal_zone (struct device*) ; 

__attribute__((used)) static ssize_t
policy_store(struct device *dev, struct device_attribute *attr,
	     const char *buf, size_t count)
{
	struct thermal_zone_device *tz = to_thermal_zone(dev);
	char name[THERMAL_NAME_LENGTH];
	int ret;

	snprintf(name, sizeof(name), "%s", buf);

	ret = thermal_zone_device_set_policy(tz, name);
	if (!ret)
		ret = count;

	return ret;
}