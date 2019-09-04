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
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int RCU_UC_EVENTS__boot_seq_done_MASK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_RAM_END ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_ci_is_smc_running (struct amdgpu_device*) ; 
 int amdgpu_ci_load_smc_ucode (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ci_reset_smc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ci_stop_smc_clock (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixRCU_UC_EVENTS ; 
 int /*<<< orphan*/  ixSMC_SYSCON_MISC_CNTL ; 

__attribute__((used)) static int ci_upload_firmware(struct amdgpu_device *adev)
{
	int i, ret;

	if (amdgpu_ci_is_smc_running(adev)) {
		DRM_INFO("smc is running, no need to load smc firmware\n");
		return 0;
	}

	for (i = 0; i < adev->usec_timeout; i++) {
		if (RREG32_SMC(ixRCU_UC_EVENTS) & RCU_UC_EVENTS__boot_seq_done_MASK)
			break;
	}
	WREG32_SMC(ixSMC_SYSCON_MISC_CNTL, 1);

	amdgpu_ci_stop_smc_clock(adev);
	amdgpu_ci_reset_smc(adev);

	ret = amdgpu_ci_load_smc_ucode(adev, SMC_RAM_END);

	return ret;

}