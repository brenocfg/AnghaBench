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
struct smu_table_context {int /*<<< orphan*/  thermal_controller_type; int /*<<< orphan*/  driver_pptable; struct smu_11_0_powerplay_table* power_play_table; } ;
struct smu_context {struct smu_table_context smu_table; } ;
struct smu_11_0_powerplay_table {int /*<<< orphan*/  thermal_controller_type; int /*<<< orphan*/  smc_pptable; } ;
typedef  int /*<<< orphan*/  PPTable_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int arcturus_store_powerplay_table(struct smu_context *smu)
{
	struct smu_11_0_powerplay_table *powerplay_table = NULL;
	struct smu_table_context *table_context = &smu->smu_table;
	int ret = 0;

	if (!table_context->power_play_table)
		return -EINVAL;

	powerplay_table = table_context->power_play_table;

	memcpy(table_context->driver_pptable, &powerplay_table->smc_pptable,
	       sizeof(PPTable_t));

	table_context->thermal_controller_type = powerplay_table->thermal_controller_type;

	return ret;
}