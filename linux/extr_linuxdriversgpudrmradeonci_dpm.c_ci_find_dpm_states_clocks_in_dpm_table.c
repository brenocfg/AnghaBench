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
typedef  size_t u32 ;
struct radeon_ps {int dummy; } ;
struct TYPE_9__ {scalar_t__ current_active_crtc_count; scalar_t__ new_active_crtc_count; } ;
struct TYPE_10__ {TYPE_4__ dpm; } ;
struct radeon_device {TYPE_5__ pm; } ;
struct ci_single_dpm_table {size_t count; TYPE_3__* dpm_levels; } ;
struct ci_ps {int performance_level_count; TYPE_2__* performance_levels; } ;
struct TYPE_6__ {struct ci_single_dpm_table mclk_table; struct ci_single_dpm_table sclk_table; } ;
struct ci_power_info {int /*<<< orphan*/  need_update_smu7_dpm_table; TYPE_1__ dpm_table; } ;
struct TYPE_8__ {size_t value; } ;
struct TYPE_7__ {size_t sclk; size_t mclk; } ;

/* Variables and functions */
 scalar_t__ CISLAND_MINIMUM_ENGINE_CLOCK ; 
 int /*<<< orphan*/  DPMTABLE_OD_UPDATE_MCLK ; 
 int /*<<< orphan*/  DPMTABLE_OD_UPDATE_SCLK ; 
 int /*<<< orphan*/  DPMTABLE_UPDATE_MCLK ; 
 int /*<<< orphan*/  DPMTABLE_UPDATE_SCLK ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 struct ci_ps* ci_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void ci_find_dpm_states_clocks_in_dpm_table(struct radeon_device *rdev,
						   struct radeon_ps *radeon_state)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct ci_ps *state = ci_get_ps(radeon_state);
	struct ci_single_dpm_table *sclk_table = &pi->dpm_table.sclk_table;
	u32 sclk = state->performance_levels[state->performance_level_count-1].sclk;
	struct ci_single_dpm_table *mclk_table = &pi->dpm_table.mclk_table;
	u32 mclk = state->performance_levels[state->performance_level_count-1].mclk;
	u32 i;

	pi->need_update_smu7_dpm_table = 0;

	for (i = 0; i < sclk_table->count; i++) {
		if (sclk == sclk_table->dpm_levels[i].value)
			break;
	}

	if (i >= sclk_table->count) {
		pi->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_SCLK;
	} else {
		/* XXX The current code always reprogrammed the sclk levels,
		 * but we don't currently handle disp sclk requirements
		 * so just skip it.
		 */
		if (CISLAND_MINIMUM_ENGINE_CLOCK != CISLAND_MINIMUM_ENGINE_CLOCK)
			pi->need_update_smu7_dpm_table |= DPMTABLE_UPDATE_SCLK;
	}

	for (i = 0; i < mclk_table->count; i++) {
		if (mclk == mclk_table->dpm_levels[i].value)
			break;
	}

	if (i >= mclk_table->count)
		pi->need_update_smu7_dpm_table |= DPMTABLE_OD_UPDATE_MCLK;

	if (rdev->pm.dpm.current_active_crtc_count !=
	    rdev->pm.dpm.new_active_crtc_count)
		pi->need_update_smu7_dpm_table |= DPMTABLE_UPDATE_MCLK;
}