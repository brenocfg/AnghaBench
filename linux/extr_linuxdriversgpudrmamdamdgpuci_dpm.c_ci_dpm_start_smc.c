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
struct amdgpu_device {int usec_timeout; } ;

/* Variables and functions */
 int FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ci_program_jump_on_start (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ci_start_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ci_start_smc_clock (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixFIRMWARE_FLAGS ; 

__attribute__((used)) static void ci_dpm_start_smc(struct amdgpu_device *adev)
{
	int i;

	amdgpu_ci_program_jump_on_start(adev);
	amdgpu_ci_start_smc_clock(adev);
	amdgpu_ci_start_smc(adev);
	for (i = 0; i < adev->usec_timeout; i++) {
		if (RREG32_SMC(ixFIRMWARE_FLAGS) & FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK)
			break;
	}
}