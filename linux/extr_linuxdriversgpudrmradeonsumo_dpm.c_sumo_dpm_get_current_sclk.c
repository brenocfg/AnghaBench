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
typedef  size_t u32 ;
struct sumo_ps {size_t num_levels; struct sumo_pl* levels; } ;
struct sumo_pl {size_t sclk; } ;
struct radeon_ps {int dummy; } ;
struct sumo_power_info {struct sumo_pl boost_pl; struct radeon_ps current_rps; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 size_t BOOST_DPM_LEVEL ; 
 size_t CURR_INDEX_MASK ; 
 size_t CURR_INDEX_SHIFT ; 
 size_t RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 struct sumo_ps* sumo_get_ps (struct radeon_ps*) ; 

u32 sumo_dpm_get_current_sclk(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	struct radeon_ps *rps = &pi->current_rps;
	struct sumo_ps *ps = sumo_get_ps(rps);
	struct sumo_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROFILE_INDEX) & CURR_INDEX_MASK) >>
		CURR_INDEX_SHIFT;

	if (current_index == BOOST_DPM_LEVEL) {
		pl = &pi->boost_pl;
		return pl->sclk;
	} else if (current_index >= ps->num_levels) {
		return 0;
	} else {
		pl = &ps->levels[current_index];
		return pl->sclk;
	}
}