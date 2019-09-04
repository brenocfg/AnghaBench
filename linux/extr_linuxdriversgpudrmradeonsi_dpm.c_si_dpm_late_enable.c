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
 int si_set_temperature_range (struct radeon_device*) ; 

int si_dpm_late_enable(struct radeon_device *rdev)
{
	int ret;

	ret = si_set_temperature_range(rdev);
	if (ret)
		return ret;

	return ret;
}