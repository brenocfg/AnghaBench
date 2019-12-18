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
struct intel_soc_dts_sensors {scalar_t__ tj_max; TYPE_1__* soc_dts; } ;
struct TYPE_2__ {int trip_count; int trip_mask; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int SOC_MAX_DTS_SENSORS ; 
 int /*<<< orphan*/  THERMAL_TRIP_CRITICAL ; 
 int update_trip_temp (TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ ) ; 

int intel_soc_dts_iosf_add_read_only_critical_trip(
	struct intel_soc_dts_sensors *sensors, int critical_offset)
{
	int i, j;

	for (i = 0; i < SOC_MAX_DTS_SENSORS; ++i) {
		for (j = 0; j < sensors->soc_dts[i].trip_count; ++j) {
			if (!(sensors->soc_dts[i].trip_mask & BIT(j))) {
				return update_trip_temp(&sensors->soc_dts[i], j,
					sensors->tj_max - critical_offset,
					THERMAL_TRIP_CRITICAL);
			}
		}
	}

	return -EINVAL;
}