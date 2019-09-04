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
struct trinity_ps {size_t num_levels; struct trinity_pl* levels; } ;
struct radeon_ps {int dummy; } ;
struct trinity_power_info {struct radeon_ps current_rps; } ;
struct trinity_pl {size_t sclk; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 size_t CURRENT_STATE_MASK ; 
 size_t CURRENT_STATE_SHIFT ; 
 size_t RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 struct trinity_ps* trinity_get_ps (struct radeon_ps*) ; 

u32 trinity_dpm_get_current_sclk(struct radeon_device *rdev)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	struct radeon_ps *rps = &pi->current_rps;
	struct trinity_ps *ps = trinity_get_ps(rps);
	struct trinity_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROFILE_INDEX) & CURRENT_STATE_MASK) >>
		CURRENT_STATE_SHIFT;

	if (current_index >= ps->num_levels) {
		return 0;
	} else {
		pl = &ps->levels[current_index];
		return pl->sclk;
	}
}