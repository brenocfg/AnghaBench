#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
struct ci_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct ci_power_info {int /*<<< orphan*/  requested_rps; } ;
struct TYPE_2__ {int /*<<< orphan*/  sclk; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 struct ci_ps* ci_get_ps (int /*<<< orphan*/ *) ; 

u32 ci_dpm_get_sclk(struct radeon_device *rdev, bool low)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct ci_ps *requested_state = ci_get_ps(&pi->requested_rps);

	if (low)
		return requested_state->performance_levels[0].sclk;
	else
		return requested_state->performance_levels[requested_state->performance_level_count - 1].sclk;
}