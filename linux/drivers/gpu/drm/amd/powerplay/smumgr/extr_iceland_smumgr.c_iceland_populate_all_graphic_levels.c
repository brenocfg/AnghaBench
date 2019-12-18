#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_11__ {int pcie_dpm_enable_mask; int /*<<< orphan*/  sclk_dpm_enable_mask; } ;
struct TYPE_14__ {size_t count; TYPE_2__* dpm_levels; } ;
struct smu7_dpm_table {TYPE_6__ sclk_table; } ;
struct smu7_hwmgr {TYPE_3__ dpm_level_enable_mask; struct smu7_dpm_table dpm_table; } ;
struct pp_hwmgr {scalar_t__ smu_backend; scalar_t__ backend; } ;
struct TYPE_12__ {int GraphicsDpmLevelCount; TYPE_5__* GraphicsLevel; } ;
struct TYPE_9__ {size_t dpm_table_start; } ;
struct iceland_smumgr {TYPE_4__ smc_state_table; TYPE_1__ smu7_data; } ;
struct TYPE_13__ {int EnabledForActivity; int pcieDpmLevel; int /*<<< orphan*/  DisplayWatermark; scalar_t__ DeepSleepDivId; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_5__ SMU71_Discrete_GraphicsLevel ;

/* Variables and functions */
 int /*<<< orphan*/  GraphicsLevel ; 
 int /*<<< orphan*/  PPSMC_DISPLAY_WATERMARK_HIGH ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 int /*<<< orphan*/  SMU71_Discrete_DpmTable ; 
 int SMU71_MAX_LEVELS_GRAPHICS ; 
 int iceland_populate_single_graphic_level (struct pp_hwmgr*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int,size_t) ; 
 size_t offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phm_get_dpm_level_enable_mask_value (TYPE_6__*) ; 
 int smu7_copy_bytes_to_smc (struct pp_hwmgr*,size_t,int*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iceland_populate_all_graphic_levels(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct iceland_smumgr *smu_data = (struct iceland_smumgr *)(hwmgr->smu_backend);
	struct smu7_dpm_table *dpm_table = &data->dpm_table;
	uint32_t level_array_adress = smu_data->smu7_data.dpm_table_start +
				offsetof(SMU71_Discrete_DpmTable, GraphicsLevel);

	uint32_t level_array_size = sizeof(SMU71_Discrete_GraphicsLevel) *
						SMU71_MAX_LEVELS_GRAPHICS;

	SMU71_Discrete_GraphicsLevel *levels = smu_data->smc_state_table.GraphicsLevel;

	uint32_t i;
	uint8_t highest_pcie_level_enabled = 0;
	uint8_t lowest_pcie_level_enabled = 0, mid_pcie_level_enabled = 0;
	uint8_t count = 0;
	int result = 0;

	memset(levels, 0x00, level_array_size);

	for (i = 0; i < dpm_table->sclk_table.count; i++) {
		result = iceland_populate_single_graphic_level(hwmgr,
					dpm_table->sclk_table.dpm_levels[i].value,
					&(smu_data->smc_state_table.GraphicsLevel[i]));
		if (result != 0)
			return result;

		/* Making sure only DPM level 0-1 have Deep Sleep Div ID populated. */
		if (i > 1)
			smu_data->smc_state_table.GraphicsLevel[i].DeepSleepDivId = 0;
	}

	/* Only enable level 0 for now. */
	smu_data->smc_state_table.GraphicsLevel[0].EnabledForActivity = 1;

	/* set highest level watermark to high */
	if (dpm_table->sclk_table.count > 1)
		smu_data->smc_state_table.GraphicsLevel[dpm_table->sclk_table.count-1].DisplayWatermark =
			PPSMC_DISPLAY_WATERMARK_HIGH;

	smu_data->smc_state_table.GraphicsDpmLevelCount =
		(uint8_t)dpm_table->sclk_table.count;
	data->dpm_level_enable_mask.sclk_dpm_enable_mask =
		phm_get_dpm_level_enable_mask_value(&dpm_table->sclk_table);

	while ((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
				(1 << (highest_pcie_level_enabled + 1))) != 0) {
		highest_pcie_level_enabled++;
	}

	while ((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
		(1 << lowest_pcie_level_enabled)) == 0) {
		lowest_pcie_level_enabled++;
	}

	while ((count < highest_pcie_level_enabled) &&
			((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
				(1 << (lowest_pcie_level_enabled + 1 + count))) == 0)) {
		count++;
	}

	mid_pcie_level_enabled = (lowest_pcie_level_enabled+1+count) < highest_pcie_level_enabled ?
		(lowest_pcie_level_enabled+1+count) : highest_pcie_level_enabled;


	/* set pcieDpmLevel to highest_pcie_level_enabled*/
	for (i = 2; i < dpm_table->sclk_table.count; i++) {
		smu_data->smc_state_table.GraphicsLevel[i].pcieDpmLevel = highest_pcie_level_enabled;
	}

	/* set pcieDpmLevel to lowest_pcie_level_enabled*/
	smu_data->smc_state_table.GraphicsLevel[0].pcieDpmLevel = lowest_pcie_level_enabled;

	/* set pcieDpmLevel to mid_pcie_level_enabled*/
	smu_data->smc_state_table.GraphicsLevel[1].pcieDpmLevel = mid_pcie_level_enabled;

	/* level count will send to smc once at init smc table and never change*/
	result = smu7_copy_bytes_to_smc(hwmgr, level_array_adress,
				(uint8_t *)levels, (uint32_t)level_array_size,
								SMC_RAM_END);

	return result;
}