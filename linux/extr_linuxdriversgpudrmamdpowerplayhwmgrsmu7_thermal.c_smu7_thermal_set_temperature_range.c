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
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_THERMAL_CTRL ; 
 int /*<<< orphan*/  CG_THERMAL_INT ; 
 int /*<<< orphan*/  DIG_THERM_DPM ; 
 int /*<<< orphan*/  DIG_THERM_INTH ; 
 int /*<<< orphan*/  DIG_THERM_INTL ; 
 int EINVAL ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int PP_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int SMU7_THERMAL_MAXIMUM_ALERT_TEMP ; 
 int SMU7_THERMAL_MINIMUM_ALERT_TEMP ; 

__attribute__((used)) static int smu7_thermal_set_temperature_range(struct pp_hwmgr *hwmgr,
		int low_temp, int high_temp)
{
	int low = SMU7_THERMAL_MINIMUM_ALERT_TEMP *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	int high = SMU7_THERMAL_MAXIMUM_ALERT_TEMP *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	if (low < low_temp)
		low = low_temp;
	if (high > high_temp)
		high = high_temp;

	if (low > high)
		return -EINVAL;

	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, DIG_THERM_INTH,
			(high / PP_TEMPERATURE_UNITS_PER_CENTIGRADES));
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, DIG_THERM_INTL,
			(low / PP_TEMPERATURE_UNITS_PER_CENTIGRADES));
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_CTRL, DIG_THERM_DPM,
			(high / PP_TEMPERATURE_UNITS_PER_CENTIGRADES));

	return 0;
}