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
struct smu_baco_context {int platform_support; int /*<<< orphan*/  mutex; } ;
struct smu_context {struct smu_baco_context smu_baco; struct smu_table_context smu_table; } ;
struct smu_11_0_powerplay_table {int platform_caps; int /*<<< orphan*/  thermal_controller_type; int /*<<< orphan*/  smc_pptable; } ;
typedef  int /*<<< orphan*/  PPTable_t ;

/* Variables and functions */
 int EINVAL ; 
 int SMU_11_0_PP_PLATFORM_CAP_BACO ; 
 int SMU_11_0_PP_PLATFORM_CAP_MACO ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int navi10_store_powerplay_table(struct smu_context *smu)
{
	struct smu_11_0_powerplay_table *powerplay_table = NULL;
	struct smu_table_context *table_context = &smu->smu_table;
	struct smu_baco_context *smu_baco = &smu->smu_baco;

	if (!table_context->power_play_table)
		return -EINVAL;

	powerplay_table = table_context->power_play_table;

	memcpy(table_context->driver_pptable, &powerplay_table->smc_pptable,
	       sizeof(PPTable_t));

	table_context->thermal_controller_type = powerplay_table->thermal_controller_type;

	mutex_lock(&smu_baco->mutex);
	if (powerplay_table->platform_caps & SMU_11_0_PP_PLATFORM_CAP_BACO ||
	    powerplay_table->platform_caps & SMU_11_0_PP_PLATFORM_CAP_MACO)
		smu_baco->platform_support = true;
	mutex_unlock(&smu_baco->mutex);

	return 0;
}