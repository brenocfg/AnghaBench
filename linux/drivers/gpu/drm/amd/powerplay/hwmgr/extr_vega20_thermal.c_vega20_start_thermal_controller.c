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
struct pp_hwmgr {int dummy; } ;
struct PP_TemperatureRange {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int vega20_thermal_enable_alert (struct pp_hwmgr*) ; 
 int vega20_thermal_set_temperature_range (struct pp_hwmgr*,struct PP_TemperatureRange*) ; 
 int vega20_thermal_setup_fan_table (struct pp_hwmgr*) ; 

int vega20_start_thermal_controller(struct pp_hwmgr *hwmgr,
				struct PP_TemperatureRange *range)
{
	int ret = 0;

	if (range == NULL)
		return -EINVAL;

	ret = vega20_thermal_set_temperature_range(hwmgr, range);
	if (ret)
		return ret;

	ret = vega20_thermal_enable_alert(hwmgr);
	if (ret)
		return ret;

	ret = vega20_thermal_setup_fan_table(hwmgr);

	return ret;
}