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
struct radeon_device {int dummy; } ;
struct ci_power_info {int uvd_power_gated; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_update_uvd_dpm (struct radeon_device*,int) ; 

void ci_dpm_powergate_uvd(struct radeon_device *rdev, bool gate)
{
	struct ci_power_info *pi = ci_get_pi(rdev);

	if (pi->uvd_power_gated == gate)
		return;

	pi->uvd_power_gated = gate;

	ci_update_uvd_dpm(rdev, gate);
}