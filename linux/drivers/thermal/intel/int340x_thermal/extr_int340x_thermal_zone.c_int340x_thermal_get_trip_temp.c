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
struct thermal_zone_device {struct int34x_thermal_zone* devdata; } ;
struct int34x_thermal_zone {int aux_trip_nr; int* aux_trips; int crt_trip_id; int crt_temp; int psv_trip_id; int psv_temp; int hot_trip_id; int hot_temp; TYPE_2__* act_trips; TYPE_1__* override_ops; } ;
struct TYPE_4__ {int id; int temp; scalar_t__ valid; } ;
struct TYPE_3__ {int (* get_trip_temp ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int INT340X_THERMAL_MAX_ACT_TRIP_COUNT ; 
 int stub1 (struct thermal_zone_device*,int,int*) ; 

__attribute__((used)) static int int340x_thermal_get_trip_temp(struct thermal_zone_device *zone,
					 int trip, int *temp)
{
	struct int34x_thermal_zone *d = zone->devdata;
	int i;

	if (d->override_ops && d->override_ops->get_trip_temp)
		return d->override_ops->get_trip_temp(zone, trip, temp);

	if (trip < d->aux_trip_nr)
		*temp = d->aux_trips[trip];
	else if (trip == d->crt_trip_id)
		*temp = d->crt_temp;
	else if (trip == d->psv_trip_id)
		*temp = d->psv_temp;
	else if (trip == d->hot_trip_id)
		*temp = d->hot_temp;
	else {
		for (i = 0; i < INT340X_THERMAL_MAX_ACT_TRIP_COUNT; i++) {
			if (d->act_trips[i].valid &&
			    d->act_trips[i].id == trip) {
				*temp = d->act_trips[i].temp;
				break;
			}
		}
		if (i == INT340X_THERMAL_MAX_ACT_TRIP_COUNT)
			return -EINVAL;
	}

	return 0;
}