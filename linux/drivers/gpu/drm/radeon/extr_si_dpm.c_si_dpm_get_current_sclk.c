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
struct rv7xx_pl {size_t sclk; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {size_t performance_level_count; struct rv7xx_pl* performance_levels; } ;
struct evergreen_power_info {struct radeon_ps current_rps; } ;

/* Variables and functions */
 size_t CURRENT_STATE_INDEX_MASK ; 
 size_t CURRENT_STATE_INDEX_SHIFT ; 
 size_t RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 

u32 si_dpm_get_current_sclk(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct radeon_ps *rps = &eg_pi->current_rps;
	struct ni_ps *ps = ni_get_ps(rps);
	struct rv7xx_pl *pl;
	u32 current_index =
		(RREG32(TARGET_AND_CURRENT_PROFILE_INDEX) & CURRENT_STATE_INDEX_MASK) >>
		CURRENT_STATE_INDEX_SHIFT;

	if (current_index >= ps->performance_level_count) {
		return 0;
	} else {
		pl = &ps->performance_levels[current_index];
		return pl->sclk;
	}
}