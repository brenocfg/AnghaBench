#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  disable_water_mark; } ;
struct TYPE_6__ {int /*<<< orphan*/  water_marks_table; } ;
struct vega20_hwmgr {int /*<<< orphan*/  water_marks_bitmap; TYPE_2__* smu_features; TYPE_1__ registry_data; TYPE_3__ smc_state_table; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
struct dm_pp_wm_sets_with_clock_ranges_soc15 {int dummy; } ;
typedef  int /*<<< orphan*/  Watermarks_t ;
struct TYPE_5__ {scalar_t__ supported; } ;

/* Variables and functions */
 size_t GNLD_DPM_DCEFCLK ; 
 size_t GNLD_DPM_SOCCLK ; 
 int /*<<< orphan*/  WaterMarksExist ; 
 int /*<<< orphan*/  WaterMarksLoaded ; 
 int /*<<< orphan*/  smu_set_watermarks_for_clocks_ranges (int /*<<< orphan*/ *,struct dm_pp_wm_sets_with_clock_ranges_soc15*) ; 

__attribute__((used)) static int vega20_set_watermarks_for_clocks_ranges(struct pp_hwmgr *hwmgr,
						   void *clock_ranges)
{
	struct vega20_hwmgr *data = (struct vega20_hwmgr *)(hwmgr->backend);
	Watermarks_t *table = &(data->smc_state_table.water_marks_table);
	struct dm_pp_wm_sets_with_clock_ranges_soc15 *wm_with_clock_ranges = clock_ranges;

	if (!data->registry_data.disable_water_mark &&
	    data->smu_features[GNLD_DPM_DCEFCLK].supported &&
	    data->smu_features[GNLD_DPM_SOCCLK].supported) {
		smu_set_watermarks_for_clocks_ranges(table, wm_with_clock_ranges);
		data->water_marks_bitmap |= WaterMarksExist;
		data->water_marks_bitmap &= ~WaterMarksLoaded;
	}

	return 0;
}