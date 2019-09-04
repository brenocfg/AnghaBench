#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct nvkm_therm {struct nvbios_therm_trip_point* last_trip; TYPE_3__* fan; TYPE_1__* func; } ;
struct nvbios_therm_trip_point {scalar_t__ temp; scalar_t__ hysteresis; size_t fan_duty; } ;
struct TYPE_5__ {size_t nr_fan_trip; struct nvbios_therm_trip_point* trip; } ;
struct TYPE_6__ {TYPE_2__ bios; } ;
struct TYPE_4__ {scalar_t__ (* temp_get ) (struct nvkm_therm*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct nvkm_therm*) ; 

__attribute__((used)) static int
nvkm_therm_update_trip(struct nvkm_therm *therm)
{
	struct nvbios_therm_trip_point *trip = therm->fan->bios.trip,
				       *cur_trip = NULL,
				       *last_trip = therm->last_trip;
	u8  temp = therm->func->temp_get(therm);
	u16 duty, i;

	/* look for the trip point corresponding to the current temperature */
	cur_trip = NULL;
	for (i = 0; i < therm->fan->bios.nr_fan_trip; i++) {
		if (temp >= trip[i].temp)
			cur_trip = &trip[i];
	}

	/* account for the hysteresis cycle */
	if (last_trip && temp <= (last_trip->temp) &&
	    temp > (last_trip->temp - last_trip->hysteresis))
		cur_trip = last_trip;

	if (cur_trip) {
		duty = cur_trip->fan_duty;
		therm->last_trip = cur_trip;
	} else {
		duty = 0;
		therm->last_trip = NULL;
	}

	return duty;
}