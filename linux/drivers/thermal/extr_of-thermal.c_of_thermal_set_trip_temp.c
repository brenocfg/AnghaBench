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
struct thermal_zone_device {struct __thermal_zone* devdata; } ;
struct __thermal_zone {int ntrips; TYPE_1__* trips; int /*<<< orphan*/  sensor_data; TYPE_2__* ops; } ;
struct TYPE_4__ {int (* set_trip_temp ) (int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_3__ {int temperature; } ;

/* Variables and functions */
 int EDOM ; 
 int stub1 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int of_thermal_set_trip_temp(struct thermal_zone_device *tz, int trip,
				    int temp)
{
	struct __thermal_zone *data = tz->devdata;

	if (trip >= data->ntrips || trip < 0)
		return -EDOM;

	if (data->ops->set_trip_temp) {
		int ret;

		ret = data->ops->set_trip_temp(data->sensor_data, trip, temp);
		if (ret)
			return ret;
	}

	/* thermal framework should take care of data->mask & (1 << trip) */
	data->trips[trip].temperature = temp;

	return 0;
}