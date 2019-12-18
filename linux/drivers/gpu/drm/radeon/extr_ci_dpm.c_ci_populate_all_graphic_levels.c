#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct radeon_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  sclk_dpm_enable_mask; } ;
struct TYPE_9__ {scalar_t__ GraphicsDpmLevelCount; TYPE_4__* GraphicsLevel; } ;
struct TYPE_12__ {size_t count; TYPE_1__* dpm_levels; } ;
struct ci_dpm_table {TYPE_7__ sclk_table; } ;
struct ci_power_info {size_t dpm_table_start; int /*<<< orphan*/  sram_end; TYPE_3__ dpm_level_enable_mask; TYPE_2__ smc_state_table; scalar_t__* activity_target; struct ci_dpm_table dpm_table; } ;
struct TYPE_11__ {int EnabledForActivity; int /*<<< orphan*/  DisplayWatermark; scalar_t__ DeepSleepDivId; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ SMU7_Discrete_GraphicsLevel ;

/* Variables and functions */
 int /*<<< orphan*/  GraphicsLevel ; 
 int /*<<< orphan*/  PPSMC_DISPLAY_WATERMARK_HIGH ; 
 int /*<<< orphan*/  SMU7_Discrete_DpmTable ; 
 int SMU7_MAX_LEVELS_GRAPHICS ; 
 size_t ci_copy_bytes_to_smc (struct radeon_device*,size_t,scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_get_dpm_level_enable_mask_value (TYPE_7__*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 size_t ci_populate_single_graphic_level (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,size_t) ; 
 size_t offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_populate_all_graphic_levels(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct ci_dpm_table *dpm_table = &pi->dpm_table;
	u32 level_array_address = pi->dpm_table_start +
		offsetof(SMU7_Discrete_DpmTable, GraphicsLevel);
	u32 level_array_size = sizeof(SMU7_Discrete_GraphicsLevel) *
		SMU7_MAX_LEVELS_GRAPHICS;
	SMU7_Discrete_GraphicsLevel *levels = pi->smc_state_table.GraphicsLevel;
	u32 i, ret;

	memset(levels, 0, level_array_size);

	for (i = 0; i < dpm_table->sclk_table.count; i++) {
		ret = ci_populate_single_graphic_level(rdev,
						       dpm_table->sclk_table.dpm_levels[i].value,
						       (u16)pi->activity_target[i],
						       &pi->smc_state_table.GraphicsLevel[i]);
		if (ret)
			return ret;
		if (i > 1)
			pi->smc_state_table.GraphicsLevel[i].DeepSleepDivId = 0;
		if (i == (dpm_table->sclk_table.count - 1))
			pi->smc_state_table.GraphicsLevel[i].DisplayWatermark =
				PPSMC_DISPLAY_WATERMARK_HIGH;
	}
	pi->smc_state_table.GraphicsLevel[0].EnabledForActivity = 1;

	pi->smc_state_table.GraphicsDpmLevelCount = (u8)dpm_table->sclk_table.count;
	pi->dpm_level_enable_mask.sclk_dpm_enable_mask =
		ci_get_dpm_level_enable_mask_value(&dpm_table->sclk_table);

	ret = ci_copy_bytes_to_smc(rdev, level_array_address,
				   (u8 *)levels, level_array_size,
				   pi->sram_end);
	if (ret)
		return ret;

	return 0;
}