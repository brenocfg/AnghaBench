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
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int GLOBAL_PWRMGT_EN ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

bool rv770_dpm_enabled(struct radeon_device *rdev)
{
	if (RREG32(GENERAL_PWRMGT) & GLOBAL_PWRMGT_EN)
		return true;
	else
		return false;
}