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
struct TYPE_2__ {scalar_t__ disable_uvd_powertune; } ;
struct si_power_info {TYPE_1__ dyn_powertune_data; } ;
struct radeon_ps {scalar_t__ dclk; scalar_t__ vclk; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static bool si_should_disable_uvd_powertune(struct radeon_device *rdev,
					    struct radeon_ps *radeon_state)
{
	struct si_power_info *si_pi = si_get_pi(rdev);

	if (si_pi->dyn_powertune_data.disable_uvd_powertune &&
	    radeon_state->vclk && radeon_state->dclk)
		return true;

	return false;
}