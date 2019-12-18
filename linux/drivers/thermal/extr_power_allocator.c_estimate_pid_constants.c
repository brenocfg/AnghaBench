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
typedef  int u32 ;
struct thermal_zone_device {TYPE_2__* tzp; TYPE_1__* ops; } ;
struct TYPE_4__ {int k_po; int k_pu; int k_i; } ;
struct TYPE_3__ {int (* get_trip_temp ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int int_to_frac (int) ; 
 int stub1 (struct thermal_zone_device*,int,int*) ; 

__attribute__((used)) static void estimate_pid_constants(struct thermal_zone_device *tz,
				   u32 sustainable_power, int trip_switch_on,
				   int control_temp, bool force)
{
	int ret;
	int switch_on_temp;
	u32 temperature_threshold;

	ret = tz->ops->get_trip_temp(tz, trip_switch_on, &switch_on_temp);
	if (ret)
		switch_on_temp = 0;

	temperature_threshold = control_temp - switch_on_temp;
	/*
	 * estimate_pid_constants() tries to find appropriate default
	 * values for thermal zones that don't provide them. If a
	 * system integrator has configured a thermal zone with two
	 * passive trip points at the same temperature, that person
	 * hasn't put any effort to set up the thermal zone properly
	 * so just give up.
	 */
	if (!temperature_threshold)
		return;

	if (!tz->tzp->k_po || force)
		tz->tzp->k_po = int_to_frac(sustainable_power) /
			temperature_threshold;

	if (!tz->tzp->k_pu || force)
		tz->tzp->k_pu = int_to_frac(2 * sustainable_power) /
			temperature_threshold;

	if (!tz->tzp->k_i || force)
		tz->tzp->k_i = int_to_frac(10) / 1000;
	/*
	 * The default for k_d and integral_cutoff is 0, so we can
	 * leave them as they are.
	 */
}