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
typedef  int uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  ECPU_SOFT_RESET ; 
 int ETIMEDOUT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE_SOFT_RESET ; 
 int VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmVCE_STATUS ; 

__attribute__((used)) static int vce_v3_0_firmware_loaded(struct amdgpu_device *adev)
{
	int i, j;

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 100; ++j) {
			uint32_t status = RREG32(mmVCE_STATUS);

			if (status & VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK)
				return 0;
			mdelay(10);
		}

		DRM_ERROR("VCE not responding, trying to reset the ECPU!!!\n");
		WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 1);
		mdelay(10);
		WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 0);
		mdelay(10);
	}

	return -ETIMEDOUT;
}