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
struct smu_temperature_range {int max; } ;
struct smu_table_context {struct smu_11_0_powerplay_table* power_play_table; } ;
struct smu_context {struct smu_table_context smu_table; } ;
struct smu_11_0_powerplay_table {int software_shutdown_temp; } ;

/* Variables and functions */
 int EINVAL ; 
 int SMU_TEMPERATURE_UNITS_PER_CENTIGRADES ; 

__attribute__((used)) static int navi10_get_thermal_temperature_range(struct smu_context *smu,
						struct smu_temperature_range *range)
{
	struct smu_table_context *table_context = &smu->smu_table;
	struct smu_11_0_powerplay_table *powerplay_table = table_context->power_play_table;

	if (!range || !powerplay_table)
		return -EINVAL;

	range->max = powerplay_table->software_shutdown_temp *
		SMU_TEMPERATURE_UNITS_PER_CENTIGRADES;

	return 0;
}