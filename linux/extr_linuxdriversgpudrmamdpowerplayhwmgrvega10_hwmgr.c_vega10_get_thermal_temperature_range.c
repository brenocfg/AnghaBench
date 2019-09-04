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
struct pp_hwmgr {scalar_t__ pptable; } ;
struct phm_ppt_v2_information {TYPE_1__* tdp_table; } ;
struct PP_TemperatureRange {int max; } ;
struct TYPE_2__ {int usSoftwareShutdownTemp; } ;

/* Variables and functions */
 int PP_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int /*<<< orphan*/ * SMU7ThermalWithDelayPolicy ; 
 int /*<<< orphan*/  memcpy (struct PP_TemperatureRange*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vega10_get_thermal_temperature_range(struct pp_hwmgr *hwmgr,
		struct PP_TemperatureRange *thermal_data)
{
	struct phm_ppt_v2_information *table_info =
			(struct phm_ppt_v2_information *)hwmgr->pptable;

	memcpy(thermal_data, &SMU7ThermalWithDelayPolicy[0], sizeof(struct PP_TemperatureRange));

	thermal_data->max = table_info->tdp_table->usSoftwareShutdownTemp *
		PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	return 0;
}