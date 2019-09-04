#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ u8 ;
struct TYPE_7__ {int /*<<< orphan*/  sclk_dpm_enable_mask; } ;
struct TYPE_8__ {size_t count; TYPE_1__* dpm_levels; } ;
struct smu7_dpm_table {TYPE_4__ sclk_table; } ;
struct smu7_hwmgr {TYPE_3__ dpm_level_enable_mask; struct smu7_dpm_table dpm_table; } ;
struct pp_hwmgr {scalar_t__ smu_backend; scalar_t__ backend; } ;
struct TYPE_6__ {scalar_t__ GraphicsDpmLevelCount; struct SMU7_Discrete_GraphicsLevel* GraphicsLevel; } ;
struct ci_smumgr {size_t dpm_table_start; TYPE_2__ smc_state_table; } ;
struct SMU7_Discrete_GraphicsLevel {int EnabledForActivity; int /*<<< orphan*/  DisplayWatermark; scalar_t__ DeepSleepDivId; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  GraphicsLevel ; 
 int /*<<< orphan*/  PPSMC_DISPLAY_WATERMARK_HIGH ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 int /*<<< orphan*/  SMU7_Discrete_DpmTable ; 
 int SMU7_MAX_LEVELS_GRAPHICS ; 
 int ci_copy_bytes_to_smc (struct pp_hwmgr*,size_t,scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 int ci_populate_single_graphic_level (struct pp_hwmgr*,int /*<<< orphan*/ ,struct SMU7_Discrete_GraphicsLevel*) ; 
 size_t offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_get_dpm_level_enable_mask_value (TYPE_4__*) ; 

__attribute__((used)) static int ci_populate_all_graphic_levels(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct ci_smumgr *smu_data = (struct ci_smumgr *)(hwmgr->smu_backend);
	struct smu7_dpm_table *dpm_table = &data->dpm_table;
	int result = 0;
	uint32_t array = smu_data->dpm_table_start +
			offsetof(SMU7_Discrete_DpmTable, GraphicsLevel);
	uint32_t array_size = sizeof(struct SMU7_Discrete_GraphicsLevel) *
			SMU7_MAX_LEVELS_GRAPHICS;
	struct SMU7_Discrete_GraphicsLevel *levels =
			smu_data->smc_state_table.GraphicsLevel;
	uint32_t i;

	for (i = 0; i < dpm_table->sclk_table.count; i++) {
		result = ci_populate_single_graphic_level(hwmgr,
				dpm_table->sclk_table.dpm_levels[i].value,
				&levels[i]);
		if (result)
			return result;
		if (i > 1)
			smu_data->smc_state_table.GraphicsLevel[i].DeepSleepDivId = 0;
		if (i == (dpm_table->sclk_table.count - 1))
			smu_data->smc_state_table.GraphicsLevel[i].DisplayWatermark =
				PPSMC_DISPLAY_WATERMARK_HIGH;
	}

	smu_data->smc_state_table.GraphicsLevel[0].EnabledForActivity = 1;

	smu_data->smc_state_table.GraphicsDpmLevelCount = (u8)dpm_table->sclk_table.count;
	data->dpm_level_enable_mask.sclk_dpm_enable_mask =
		phm_get_dpm_level_enable_mask_value(&dpm_table->sclk_table);

	result = ci_copy_bytes_to_smc(hwmgr, array,
				   (u8 *)levels, array_size,
				   SMC_RAM_END);

	return result;

}