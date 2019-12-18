#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sumo_ps {int flags; size_t num_levels; TYPE_2__* levels; } ;
struct TYPE_3__ {size_t min_sclk; } ;
struct sumo_power_info {scalar_t__ enable_boost; TYPE_1__ sys_info; } ;
struct radeon_ps {int class; int class2; } ;
struct radeon_device {int dummy; } ;
struct TYPE_4__ {size_t vddc_index; size_t sclk; int ss_divider_index; int ds_divider_index; int allow_gnb_slow; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION2_MVC ; 
 int ATOM_PPLIB_CLASSIFICATION_HDSTATE ; 
 int ATOM_PPLIB_CLASSIFICATION_SDSTATE ; 
 int ATOM_PPLIB_CLASSIFICATION_THERMAL ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_BATTERY ; 
 int ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE ; 
 int ATOM_PPLIB_CLASSIFICATION_UVDSTATE ; 
 size_t SUMO_MINIMUM_ENGINE_CLOCK ; 
 int SUMO_POWERSTATE_FLAGS_BOOST_STATE ; 
 int SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 struct sumo_ps* sumo_get_ps (struct radeon_ps*) ; 
 void* sumo_get_sleep_divider_id_from_clock (struct radeon_device*,size_t,size_t) ; 
 size_t sumo_get_valid_engine_clock (struct radeon_device*,size_t) ; 
 void sumo_patch_thermal_state (struct radeon_device*,struct sumo_ps*,struct sumo_ps*) ; 

__attribute__((used)) static void sumo_apply_state_adjust_rules(struct radeon_device *rdev,
					  struct radeon_ps *new_rps,
					  struct radeon_ps *old_rps)
{
	struct sumo_ps *ps = sumo_get_ps(new_rps);
	struct sumo_ps *current_ps = sumo_get_ps(old_rps);
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	u32 min_voltage = 0; /* ??? */
	u32 min_sclk = pi->sys_info.min_sclk; /* XXX check against disp reqs */
	u32 sclk_in_sr = pi->sys_info.min_sclk; /* ??? */
	u32 i;

	if (new_rps->class & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		return sumo_patch_thermal_state(rdev, ps, current_ps);

	if (pi->enable_boost) {
		if (new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_PERFORMANCE)
			ps->flags |= SUMO_POWERSTATE_FLAGS_BOOST_STATE;
	}

	if ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UI_BATTERY) ||
	    (new_rps->class & ATOM_PPLIB_CLASSIFICATION_SDSTATE) ||
	    (new_rps->class & ATOM_PPLIB_CLASSIFICATION_HDSTATE))
		ps->flags |= SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE;

	for (i = 0; i < ps->num_levels; i++) {
		if (ps->levels[i].vddc_index < min_voltage)
			ps->levels[i].vddc_index = min_voltage;

		if (ps->levels[i].sclk < min_sclk)
			ps->levels[i].sclk =
				sumo_get_valid_engine_clock(rdev, min_sclk);

		ps->levels[i].ss_divider_index =
			sumo_get_sleep_divider_id_from_clock(rdev, ps->levels[i].sclk, sclk_in_sr);

		ps->levels[i].ds_divider_index =
			sumo_get_sleep_divider_id_from_clock(rdev, ps->levels[i].sclk, SUMO_MINIMUM_ENGINE_CLOCK);

		if (ps->levels[i].ds_divider_index > ps->levels[i].ss_divider_index + 1)
			ps->levels[i].ds_divider_index = ps->levels[i].ss_divider_index + 1;

		if (ps->levels[i].ss_divider_index == ps->levels[i].ds_divider_index) {
			if (ps->levels[i].ss_divider_index > 1)
				ps->levels[i].ss_divider_index = ps->levels[i].ss_divider_index - 1;
		}

		if (ps->levels[i].ss_divider_index == 0)
			ps->levels[i].ds_divider_index = 0;

		if (ps->levels[i].ds_divider_index == 0)
			ps->levels[i].ss_divider_index = 0;

		if (ps->flags & SUMO_POWERSTATE_FLAGS_FORCE_NBPS1_STATE)
			ps->levels[i].allow_gnb_slow = 1;
		else if ((new_rps->class & ATOM_PPLIB_CLASSIFICATION_UVDSTATE) ||
			 (new_rps->class2 & ATOM_PPLIB_CLASSIFICATION2_MVC))
			ps->levels[i].allow_gnb_slow = 0;
		else if (i == ps->num_levels - 1)
			ps->levels[i].allow_gnb_slow = 0;
		else
			ps->levels[i].allow_gnb_slow = 1;
	}
}