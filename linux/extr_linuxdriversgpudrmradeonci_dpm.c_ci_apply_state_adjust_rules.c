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
typedef  scalar_t__ u32 ;
struct radeon_ps {int class; scalar_t__ vce_active; scalar_t__ ecclk; scalar_t__ evclk; } ;
struct radeon_clock_and_voltage_limits {scalar_t__ mclk; scalar_t__ sclk; } ;
struct TYPE_6__ {struct radeon_clock_and_voltage_limits max_clock_voltage_on_dc; struct radeon_clock_and_voltage_limits max_clock_voltage_on_ac; } ;
struct TYPE_8__ {size_t vce_level; int new_active_crtc_count; int ac_power; TYPE_2__* vce_states; TYPE_1__ dyn_state; } ;
struct TYPE_9__ {TYPE_3__ dpm; } ;
struct radeon_device {TYPE_4__ pm; } ;
struct ci_ps {int performance_level_count; TYPE_5__* performance_levels; } ;
struct ci_power_info {int battery_state; } ;
struct TYPE_10__ {scalar_t__ mclk; scalar_t__ sclk; } ;
struct TYPE_7__ {scalar_t__ sclk; scalar_t__ mclk; scalar_t__ ecclk; scalar_t__ evclk; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION_UI_BATTERY ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_MASK ; 
 scalar_t__ ci_dpm_vblank_too_short (struct radeon_device*) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 struct ci_ps* ci_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void ci_apply_state_adjust_rules(struct radeon_device *rdev,
					struct radeon_ps *rps)
{
	struct ci_ps *ps = ci_get_ps(rps);
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct radeon_clock_and_voltage_limits *max_limits;
	bool disable_mclk_switching;
	u32 sclk, mclk;
	int i;

	if (rps->vce_active) {
		rps->evclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].evclk;
		rps->ecclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].ecclk;
	} else {
		rps->evclk = 0;
		rps->ecclk = 0;
	}

	if ((rdev->pm.dpm.new_active_crtc_count > 1) ||
	    ci_dpm_vblank_too_short(rdev))
		disable_mclk_switching = true;
	else
		disable_mclk_switching = false;

	if ((rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) == ATOM_PPLIB_CLASSIFICATION_UI_BATTERY)
		pi->battery_state = true;
	else
		pi->battery_state = false;

	if (rdev->pm.dpm.ac_power)
		max_limits = &rdev->pm.dpm.dyn_state.max_clock_voltage_on_ac;
	else
		max_limits = &rdev->pm.dpm.dyn_state.max_clock_voltage_on_dc;

	if (rdev->pm.dpm.ac_power == false) {
		for (i = 0; i < ps->performance_level_count; i++) {
			if (ps->performance_levels[i].mclk > max_limits->mclk)
				ps->performance_levels[i].mclk = max_limits->mclk;
			if (ps->performance_levels[i].sclk > max_limits->sclk)
				ps->performance_levels[i].sclk = max_limits->sclk;
		}
	}

	/* XXX validate the min clocks required for display */

	if (disable_mclk_switching) {
		mclk  = ps->performance_levels[ps->performance_level_count - 1].mclk;
		sclk = ps->performance_levels[0].sclk;
	} else {
		mclk = ps->performance_levels[0].mclk;
		sclk = ps->performance_levels[0].sclk;
	}

	if (rps->vce_active) {
		if (sclk < rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk)
			sclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk;
		if (mclk < rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].mclk)
			mclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].mclk;
	}

	ps->performance_levels[0].sclk = sclk;
	ps->performance_levels[0].mclk = mclk;

	if (ps->performance_levels[1].sclk < ps->performance_levels[0].sclk)
		ps->performance_levels[1].sclk = ps->performance_levels[0].sclk;

	if (disable_mclk_switching) {
		if (ps->performance_levels[0].mclk < ps->performance_levels[1].mclk)
			ps->performance_levels[0].mclk = ps->performance_levels[1].mclk;
	} else {
		if (ps->performance_levels[1].mclk < ps->performance_levels[0].mclk)
			ps->performance_levels[1].mclk = ps->performance_levels[0].mclk;
	}
}