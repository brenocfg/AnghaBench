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
struct radeon_device {int usec_timeout; } ;

/* Variables and functions */
 int CURRENT_STATE_MASK ; 
 int DYNAMIC_PM_EN ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 int TARGET_STATE_MASK ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void trinity_wait_for_dpm_enabled(struct radeon_device *rdev)
{
	int i;

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(SCLK_PWRMGT_CNTL) & DYNAMIC_PM_EN)
			break;
		udelay(1);
	}
	for (i = 0; i < rdev->usec_timeout; i++) {
		if ((RREG32(TARGET_AND_CURRENT_PROFILE_INDEX) & TARGET_STATE_MASK) == 0)
			break;
		udelay(1);
	}
	for (i = 0; i < rdev->usec_timeout; i++) {
		if ((RREG32(TARGET_AND_CURRENT_PROFILE_INDEX) & CURRENT_STATE_MASK) == 0)
			break;
		udelay(1);
	}
}