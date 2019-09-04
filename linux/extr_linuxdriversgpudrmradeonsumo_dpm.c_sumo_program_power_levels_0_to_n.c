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
struct sumo_ps {int num_levels; int flags; int /*<<< orphan*/ * levels; } ;
struct sumo_power_info {int /*<<< orphan*/  boost_pl; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 size_t BOOST_DPM_LEVEL ; 
 int SUMO_POWERSTATE_FLAGS_BOOST_STATE ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 struct sumo_ps* sumo_get_ps (struct radeon_ps*) ; 
 int /*<<< orphan*/  sumo_power_level_enable (struct radeon_device*,size_t,int) ; 
 int /*<<< orphan*/  sumo_program_power_level (struct radeon_device*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void sumo_program_power_levels_0_to_n(struct radeon_device *rdev,
					     struct radeon_ps *new_rps,
					     struct radeon_ps *old_rps)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	struct sumo_ps *new_ps = sumo_get_ps(new_rps);
	struct sumo_ps *old_ps = sumo_get_ps(old_rps);
	u32 i;
	u32 n_current_state_levels = (old_ps == NULL) ? 1 : old_ps->num_levels;

	for (i = 0; i < new_ps->num_levels; i++) {
		sumo_program_power_level(rdev, &new_ps->levels[i], i);
		sumo_power_level_enable(rdev, i, true);
	}

	for (i = new_ps->num_levels; i < n_current_state_levels; i++)
		sumo_power_level_enable(rdev, i, false);

	if (new_ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE)
		sumo_program_power_level(rdev, &pi->boost_pl, BOOST_DPM_LEVEL);
}