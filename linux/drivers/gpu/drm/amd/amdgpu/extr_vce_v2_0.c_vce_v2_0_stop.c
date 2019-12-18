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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmVCE_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmVCE_LMI_STATUS ; 
 int /*<<< orphan*/  mmVCE_SOFT_RESET ; 
 int /*<<< orphan*/  mmVCE_STATUS ; 
 int /*<<< orphan*/  mmVCE_VCPU_CNTL ; 
 scalar_t__ vce_v2_0_lmi_clean (struct amdgpu_device*) ; 
 scalar_t__ vce_v2_0_wait_for_idle (struct amdgpu_device*) ; 

__attribute__((used)) static int vce_v2_0_stop(struct amdgpu_device *adev)
{
	int i;
	int status;

	if (vce_v2_0_lmi_clean(adev)) {
		DRM_INFO("vce is not idle \n");
		return 0;
	}

	if (vce_v2_0_wait_for_idle(adev)) {
		DRM_INFO("VCE is busy, Can't set clock gating");
		return 0;
	}

	/* Stall UMC and register bus before resetting VCPU */
	WREG32_P(mmVCE_LMI_CTRL2, 1 << 8, ~(1 << 8));

	for (i = 0; i < 100; ++i) {
		status = RREG32(mmVCE_LMI_STATUS);
		if (status & 0x240)
			break;
		mdelay(1);
	}

	WREG32_P(mmVCE_VCPU_CNTL, 0, ~0x80001);

	/* put LMI, VCPU, RBC etc... into reset */
	WREG32_P(mmVCE_SOFT_RESET, 1, ~0x1);

	WREG32(mmVCE_STATUS, 0);

	return 0;
}