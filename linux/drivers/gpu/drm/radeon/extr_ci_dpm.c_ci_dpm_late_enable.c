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

/* Variables and functions */
 int /*<<< orphan*/  ci_dpm_powergate_uvd (struct radeon_device*,int) ; 
 int ci_set_temperature_range (struct radeon_device*) ; 

int ci_dpm_late_enable(struct radeon_device *rdev)
{
	int ret;

	ret = ci_set_temperature_range(rdev);
	if (ret)
		return ret;

	ci_dpm_powergate_uvd(rdev, true);

	return 0;
}