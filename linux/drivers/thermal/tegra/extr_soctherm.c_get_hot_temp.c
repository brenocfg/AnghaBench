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
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;
struct TYPE_2__ {int (* get_trip_type ) (struct thermal_zone_device*,int,int*) ;int (* get_trip_temp ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int THERMAL_TRIP_HOT ; 
 int of_thermal_get_ntrips (struct thermal_zone_device*) ; 
 int stub1 (struct thermal_zone_device*,int,int*) ; 
 int stub2 (struct thermal_zone_device*,int,int*) ; 

__attribute__((used)) static int get_hot_temp(struct thermal_zone_device *tz, int *trip, int *temp)
{
	int ntrips, i, ret;
	enum thermal_trip_type type;

	ntrips = of_thermal_get_ntrips(tz);
	if (ntrips <= 0)
		return -EINVAL;

	for (i = 0; i < ntrips; i++) {
		ret = tz->ops->get_trip_type(tz, i, &type);
		if (ret)
			return -EINVAL;
		if (type == THERMAL_TRIP_HOT) {
			ret = tz->ops->get_trip_temp(tz, i, temp);
			if (!ret)
				*trip = i;

			return ret;
		}
	}

	return -EINVAL;
}