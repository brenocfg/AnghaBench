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
 scalar_t__ rv770_is_smc_running (struct radeon_device*) ; 

bool btc_dpm_enabled(struct radeon_device *rdev)
{
	if (rv770_is_smc_running(rdev))
		return true;
	else
		return false;
}