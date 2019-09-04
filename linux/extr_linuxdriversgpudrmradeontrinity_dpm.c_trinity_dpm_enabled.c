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
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int SCLK_DPM_EN (int) ; 
 int /*<<< orphan*/  SMU_SCLK_DPM_CNTL ; 

__attribute__((used)) static bool trinity_dpm_enabled(struct radeon_device *rdev)
{
	if (RREG32_SMC(SMU_SCLK_DPM_CNTL) & SCLK_DPM_EN(1))
		return true;
	else
		return false;
}