#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct ci_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct TYPE_10__ {int count; TYPE_4__* dpm_levels; } ;
struct TYPE_8__ {int count; TYPE_2__* dpm_levels; } ;
struct ci_dpm_table {TYPE_5__ mclk_table; TYPE_3__ sclk_table; } ;
struct ci_power_info {int need_update_smu7_dpm_table; struct ci_dpm_table dpm_table; } ;
struct TYPE_9__ {void* value; } ;
struct TYPE_7__ {void* value; } ;
struct TYPE_6__ {void* mclk; void* sclk; } ;

/* Variables and functions */
 int DPMTABLE_OD_UPDATE_MCLK ; 
 int DPMTABLE_OD_UPDATE_SCLK ; 
 int DPMTABLE_UPDATE_MCLK ; 
 int DPMTABLE_UPDATE_SCLK ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 struct ci_ps* ci_get_ps (struct radeon_ps*) ; 
 int ci_populate_all_graphic_levels (struct radeon_device*) ; 
 int ci_populate_all_memory_levels (struct radeon_device*) ; 

__attribute__((used)) static int ci_populate_and_upload_sclk_mclk_dpm_levels(struct radeon_device *rdev,
						       struct radeon_ps *radeon_state)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct ci_ps *state = ci_get_ps(radeon_state);
	u32 sclk = state->performance_levels[state->performance_level_count-1].sclk;
	u32 mclk = state->performance_levels[state->performance_level_count-1].mclk;
	struct ci_dpm_table *dpm_table = &pi->dpm_table;
	int ret;

	if (!pi->need_update_smu7_dpm_table)
		return 0;

	if (pi->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_SCLK)
		dpm_table->sclk_table.dpm_levels[dpm_table->sclk_table.count-1].value = sclk;

	if (pi->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK)
		dpm_table->mclk_table.dpm_levels[dpm_table->mclk_table.count-1].value = mclk;

	if (pi->need_update_smu7_dpm_table & (DPMTABLE_OD_UPDATE_SCLK | DPMTABLE_UPDATE_SCLK)) {
		ret = ci_populate_all_graphic_levels(rdev);
		if (ret)
			return ret;
	}

	if (pi->need_update_smu7_dpm_table & (DPMTABLE_OD_UPDATE_MCLK | DPMTABLE_UPDATE_MCLK)) {
		ret = ci_populate_all_memory_levels(rdev);
		if (ret)
			return ret;
	}

	return 0;
}