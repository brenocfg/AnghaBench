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
struct TYPE_2__ {int htc_hyst_lmt; } ;
struct smu8_hwmgr {int thermal_auto_throttling_treshold; TYPE_1__ sys_info; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;
struct PP_TemperatureRange {int max; } ;

/* Variables and functions */
 int PP_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int /*<<< orphan*/ * SMU7ThermalPolicy ; 
 int /*<<< orphan*/  memcpy (struct PP_TemperatureRange*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int smu8_get_thermal_temperature_range(struct pp_hwmgr *hwmgr,
		struct PP_TemperatureRange *thermal_data)
{
	struct smu8_hwmgr *data = hwmgr->backend;

	memcpy(thermal_data, &SMU7ThermalPolicy[0], sizeof(struct PP_TemperatureRange));

	thermal_data->max = (data->thermal_auto_throttling_treshold +
			data->sys_info.htc_hyst_lmt) *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	return 0;
}