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
struct PP_TemperatureRange {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  smu7_thermal_enable_alert (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_thermal_initialize (struct pp_hwmgr*) ; 
 int smu7_thermal_set_temperature_range (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu7_thermal_start_smc_fan_control (struct pp_hwmgr*) ; 
 int smum_thermal_avfs_enable (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_thermal_setup_fan_table (struct pp_hwmgr*) ; 

int smu7_start_thermal_controller(struct pp_hwmgr *hwmgr,
				struct PP_TemperatureRange *range)
{
	int ret = 0;

	if (range == NULL)
		return -EINVAL;

	smu7_thermal_initialize(hwmgr);
	ret = smu7_thermal_set_temperature_range(hwmgr, range->min, range->max);
	if (ret)
		return -EINVAL;
	smu7_thermal_enable_alert(hwmgr);
	ret = smum_thermal_avfs_enable(hwmgr);
	if (ret)
		return -EINVAL;

/* We should restrict performance levels to low before we halt the SMC.
 * On the other hand we are still in boot state when we do this
 * so it would be pointless.
 * If this assumption changes we have to revisit this table.
 */
	smum_thermal_setup_fan_table(hwmgr);
	smu7_thermal_start_smc_fan_control(hwmgr);
	return 0;
}