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
typedef  scalar_t__ u16 ;
struct trinity_ps {size_t num_levels; int Dpm0PgNbPsLo; int Dpm0PgNbPsHi; int DpmXNbPsLo; int DpmXNbPsHi; TYPE_4__* levels; int /*<<< orphan*/  bapm_flags; } ;
struct TYPE_10__ {size_t min_sclk; int uma_channel_number; scalar_t__ nb_dpm_enable; } ;
struct trinity_power_info {TYPE_5__ sys_info; } ;
struct radeon_ps {int class; scalar_t__ ecclk; scalar_t__ evclk; scalar_t__ vce_active; } ;
struct TYPE_7__ {size_t new_active_crtc_count; size_t vce_level; TYPE_1__* vce_states; } ;
struct TYPE_8__ {TYPE_2__ dpm; } ;
struct radeon_device {TYPE_3__ pm; } ;
struct TYPE_9__ {size_t vddc_index; size_t sclk; int allow_gnb_slow; int /*<<< orphan*/  vce_wm; int /*<<< orphan*/  display_wm; scalar_t__ force_nbp_state; int /*<<< orphan*/  ds_divider_index; int /*<<< orphan*/  ss_divider_index; } ;
struct TYPE_6__ {scalar_t__ sclk; scalar_t__ ecclk; scalar_t__ evclk; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION_HDSTATE ; 
 int ATOM_PPLIB_CLASSIFICATION_SDSTATE ; 
 int ATOM_PPLIB_CLASSIFICATION_THERMAL ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_BATTERY ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_MASK ; 
 int /*<<< orphan*/  TRINITY_POWERSTATE_FLAGS_BAPM_DISABLE ; 
 int /*<<< orphan*/  sumo_get_sleep_divider_id_from_clock (struct radeon_device*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  trinity_adjust_uvd_state (struct radeon_device*,struct radeon_ps*) ; 
 int /*<<< orphan*/  trinity_calculate_display_wm (struct radeon_device*,struct trinity_ps*,size_t) ; 
 int /*<<< orphan*/  trinity_calculate_vce_wm (struct radeon_device*,scalar_t__) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 struct trinity_ps* trinity_get_ps (struct radeon_ps*) ; 
 size_t trinity_get_valid_engine_clock (struct radeon_device*,size_t) ; 
 int /*<<< orphan*/  trinity_get_vce_clock_voltage (struct radeon_device*,scalar_t__,scalar_t__,scalar_t__*) ; 
 void trinity_patch_thermal_state (struct radeon_device*,struct trinity_ps*,struct trinity_ps*) ; 

__attribute__((used)) static void trinity_apply_state_adjust_rules(struct radeon_device *rdev,
					     struct radeon_ps *new_rps,
					     struct radeon_ps *old_rps)
{
	struct trinity_ps *ps = trinity_get_ps(new_rps);
	struct trinity_ps *current_ps = trinity_get_ps(old_rps);
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	u32 min_voltage = 0; /* ??? */
	u32 min_sclk = pi->sys_info.min_sclk; /* XXX check against disp reqs */
	u32 sclk_in_sr = pi->sys_info.min_sclk; /* ??? */
	u32 i;
	u16 min_vce_voltage;
	bool force_high;
	u32 num_active_displays = rdev->pm.dpm.new_active_crtc_count;

	if (new_rps->class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		return trinity_patch_thermal_state(rdev, ps, current_ps);

	trinity_adjust_uvd_state(rdev, new_rps);

	if (new_rps->vce_active) {
		new_rps->evclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].evclk;
		new_rps->ecclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].ecclk;
	} else {
		new_rps->evclk = 0;
		new_rps->ecclk = 0;
	}

	for (i = 0; i < ps->num_levels; i++) {
		if (ps->levels[i].vddc_index < min_voltage)
			ps->levels[i].vddc_index = min_voltage;

		if (ps->levels[i].sclk < min_sclk)
			ps->levels[i].sclk =
				trinity_get_valid_engine_clock(rdev, min_sclk);

		/* patch in vce limits */
		if (new_rps->vce_active) {
			/* sclk */
			if (ps->levels[i].sclk < rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk)
				ps->levels[i].sclk = rdev->pm.dpm.vce_states[rdev->pm.dpm.vce_level].sclk;
			/* vddc */
			trinity_get_vce_clock_voltage(rdev, new_rps->evclk, new_rps->ecclk, &min_vce_voltage);
			if (ps->levels[i].vddc_index < min_vce_voltage)
				ps->levels[i].vddc_index = min_vce_voltage;
		}

		ps->levels[i].ds_divider_index =
			sumo_get_sleep_divider_id_from_clock(rdev, ps->levels[i].sclk, sclk_in_sr);

		ps->levels[i].ss_divider_index = ps->levels[i].ds_divider_index;

		ps->levels[i].allow_gnb_slow = 1;
		ps->levels[i].force_nbp_state = 0;
		ps->levels[i].display_wm =
			trinity_calculate_display_wm(rdev, ps, i);
		ps->levels[i].vce_wm =
			trinity_calculate_vce_wm(rdev, ps->levels[0].sclk);
	}

	if ((new_rps->class & (ATOM_PPLIB_CLASSIFICATION_HDSTATE | ATOM_PPLIB_CLASSIFICATION_SDSTATE)) ||
	    ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) == ATOM_PPLIB_CLASSIFICATION_UI_BATTERY))
		ps->bapm_flags |= TRINITY_POWERSTATE_FLAGS_BAPM_DISABLE;

	if (pi->sys_info.nb_dpm_enable) {
		ps->Dpm0PgNbPsLo = 0x1;
		ps->Dpm0PgNbPsHi = 0x0;
		ps->DpmXNbPsLo = 0x2;
		ps->DpmXNbPsHi = 0x1;

		if ((new_rps->class & (ATOM_PPLIB_CLASSIFICATION_HDSTATE | ATOM_PPLIB_CLASSIFICATION_SDSTATE)) ||
		    ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_MASK) == ATOM_PPLIB_CLASSIFICATION_UI_BATTERY)) {
			force_high = ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_HDSTATE) ||
				      ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_SDSTATE) &&
				       (pi->sys_info.uma_channel_number == 1)));
			force_high = (num_active_displays >= 3) || force_high;
			ps->Dpm0PgNbPsLo = force_high ? 0x2 : 0x3;
			ps->Dpm0PgNbPsHi = 0x1;
			ps->DpmXNbPsLo = force_high ? 0x2 : 0x3;
			ps->DpmXNbPsHi = 0x2;
			ps->levels[ps->num_levels - 1].allow_gnb_slow = 0;
		}
	}
}