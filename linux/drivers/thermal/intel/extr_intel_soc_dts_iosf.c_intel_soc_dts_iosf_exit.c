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
struct intel_soc_dts_sensors {int /*<<< orphan*/ * soc_dts; } ;

/* Variables and functions */
 int SOC_MAX_DTS_SENSORS ; 
 int /*<<< orphan*/  kfree (struct intel_soc_dts_sensors*) ; 
 int /*<<< orphan*/  remove_dts_thermal_zone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_trip_temp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_soc_dts_iosf_exit(struct intel_soc_dts_sensors *sensors)
{
	int i;

	for (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) {
		update_trip_temp(&sensors->soc_dts[i], 0, 0, 0);
		update_trip_temp(&sensors->soc_dts[i], 1, 0, 0);
		remove_dts_thermal_zone(&sensors->soc_dts[i]);
	}
	kfree(sensors);
}