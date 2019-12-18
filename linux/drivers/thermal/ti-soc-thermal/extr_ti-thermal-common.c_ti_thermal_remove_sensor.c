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
struct ti_thermal_data {scalar_t__ ti_thermal; scalar_t__ our_zone; } ;
struct ti_bandgap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  thermal_zone_device_unregister (scalar_t__) ; 
 struct ti_thermal_data* ti_bandgap_get_sensor_data (struct ti_bandgap*,int) ; 

int ti_thermal_remove_sensor(struct ti_bandgap *bgp, int id)
{
	struct ti_thermal_data *data;

	data = ti_bandgap_get_sensor_data(bgp, id);

	if (data && data->ti_thermal) {
		if (data->our_zone)
			thermal_zone_device_unregister(data->ti_thermal);
	}

	return 0;
}