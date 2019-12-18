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
 int /*<<< orphan*/  vega12_thermal_enable_alert (struct pp_hwmgr*) ; 
 int vega12_thermal_set_temperature_range (struct pp_hwmgr*,struct PP_TemperatureRange*) ; 
 int vega12_thermal_setup_fan_table (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  vega12_thermal_start_smc_fan_control (struct pp_hwmgr*) ; 

int vega12_start_thermal_controller(struct pp_hwmgr *hwmgr,
				struct PP_TemperatureRange *range)
{
	int ret = 0;

	if (range == NULL)
		return -EINVAL;

	ret = vega12_thermal_set_temperature_range(hwmgr, range);
	if (ret)
		return -EINVAL;

	vega12_thermal_enable_alert(hwmgr);
	/* We should restrict performance levels to low before we halt the SMC.
	 * On the other hand we are still in boot state when we do this
	 * so it would be pointless.
	 * If this assumption changes we have to revisit this table.
	 */
	ret = vega12_thermal_setup_fan_table(hwmgr);
	if (ret)
		return -EINVAL;

	vega12_thermal_start_smc_fan_control(hwmgr);

	return 0;
}