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
typedef  enum radeon_int_thermal_type { ____Placeholder_radeon_int_thermal_type } radeon_int_thermal_type ;

/* Variables and functions */
#define  THERMAL_TYPE_ADT7473_WITH_INTERNAL 140 
#define  THERMAL_TYPE_CI 139 
#define  THERMAL_TYPE_EMC2103_WITH_INTERNAL 138 
#define  THERMAL_TYPE_EVERGREEN 137 
#define  THERMAL_TYPE_EXTERNAL 136 
#define  THERMAL_TYPE_EXTERNAL_GPIO 135 
#define  THERMAL_TYPE_KV 134 
#define  THERMAL_TYPE_NI 133 
#define  THERMAL_TYPE_NONE 132 
#define  THERMAL_TYPE_RV6XX 131 
#define  THERMAL_TYPE_RV770 130 
#define  THERMAL_TYPE_SI 129 
#define  THERMAL_TYPE_SUMO 128 

bool r600_is_internal_thermal_sensor(enum radeon_int_thermal_type sensor)
{
	switch (sensor) {
	case THERMAL_TYPE_RV6XX:
	case THERMAL_TYPE_RV770:
	case THERMAL_TYPE_EVERGREEN:
	case THERMAL_TYPE_SUMO:
	case THERMAL_TYPE_NI:
	case THERMAL_TYPE_SI:
	case THERMAL_TYPE_CI:
	case THERMAL_TYPE_KV:
		return true;
	case THERMAL_TYPE_ADT7473_WITH_INTERNAL:
	case THERMAL_TYPE_EMC2103_WITH_INTERNAL:
		return false; /* need special handling */
	case THERMAL_TYPE_NONE:
	case THERMAL_TYPE_EXTERNAL:
	case THERMAL_TYPE_EXTERNAL_GPIO:
	default:
		return false;
	}
}