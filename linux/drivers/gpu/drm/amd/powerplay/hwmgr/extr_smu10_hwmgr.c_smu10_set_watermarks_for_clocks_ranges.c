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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct smu10_hwmgr {int water_marks_exist; int /*<<< orphan*/  water_marks_table; } ;
struct pp_hwmgr {struct smu10_hwmgr* backend; } ;
struct dm_pp_wm_sets_with_clock_ranges_soc15 {int dummy; } ;
typedef  int /*<<< orphan*/  Watermarks_t ;

/* Variables and functions */
 scalar_t__ SMU10_WMTABLE ; 
 int /*<<< orphan*/  smu_set_watermarks_for_clocks_ranges (int /*<<< orphan*/ *,struct dm_pp_wm_sets_with_clock_ranges_soc15*) ; 
 int /*<<< orphan*/  smum_smc_table_manager (struct pp_hwmgr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu10_set_watermarks_for_clocks_ranges(struct pp_hwmgr *hwmgr,
		void *clock_ranges)
{
	struct smu10_hwmgr *data = hwmgr->backend;
	struct dm_pp_wm_sets_with_clock_ranges_soc15 *wm_with_clock_ranges = clock_ranges;
	Watermarks_t *table = &(data->water_marks_table);
	int result = 0;

	smu_set_watermarks_for_clocks_ranges(table,wm_with_clock_ranges);
	smum_smc_table_manager(hwmgr, (uint8_t *)table, (uint16_t)SMU10_WMTABLE, false);
	data->water_marks_exist = true;
	return result;
}