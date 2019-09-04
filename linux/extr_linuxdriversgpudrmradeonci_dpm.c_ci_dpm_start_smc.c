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
 int /*<<< orphan*/  FIRMWARE_FLAGS ; 
 int INTERRUPTS_ENABLED ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ci_program_jump_on_start (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_start_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_start_smc_clock (struct radeon_device*) ; 

__attribute__((used)) static void ci_dpm_start_smc(struct radeon_device *rdev)
{
	int i;

	ci_program_jump_on_start(rdev);
	ci_start_smc_clock(rdev);
	ci_start_smc(rdev);
	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32_SMC(FIRMWARE_FLAGS) & INTERRUPTS_ENABLED)
			break;
	}
}