#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {TYPE_2__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int (* get_trip_hyst ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int sprintf (char*,char*,int) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int stub1 (struct thermal_zone_device*,int,int*) ; 
 struct thermal_zone_device* to_thermal_zone (struct device*) ; 

__attribute__((used)) static ssize_t
trip_point_hyst_show(struct device *dev, struct device_attribute *attr,
		     char *buf)
{
	struct thermal_zone_device *tz = to_thermal_zone(dev);
	int trip, ret;
	int temperature;

	if (!tz->ops->get_trip_hyst)
		return -EPERM;

	if (sscanf(attr->attr.name, "trip_point_%d_hyst", &trip) != 1)
		return -EINVAL;

	ret = tz->ops->get_trip_hyst(tz, trip, &temperature);

	return ret ? ret : sprintf(buf, "%d\n", temperature);
}