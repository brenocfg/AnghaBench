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
 int RREG32 (int /*<<< orphan*/ ) ; 
 int UVD_SOFT_RESET__LMI_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK ; 
 int UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mmUVD_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_LMI_STATUS ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int mmUVD_VCPU_CNTL ; 
 int /*<<< orphan*/  uvd_v4_2_set_dcm (struct amdgpu_device*,int) ; 

__attribute__((used)) static void uvd_v4_2_stop(struct amdgpu_device *adev)
{
	uint32_t i, j;
	uint32_t status;

	WREG32(mmUVD_RBC_RB_CNTL, 0x11010101);

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 100; ++j) {
			status = RREG32(mmUVD_STATUS);
			if (status & 2)
				break;
			mdelay(1);
		}
		if (status & 2)
			break;
	}

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 100; ++j) {
			status = RREG32(mmUVD_LMI_STATUS);
			if (status & 0xf)
				break;
			mdelay(1);
		}
		if (status & 0xf)
			break;
	}

	/* Stall UMC and register bus before resetting VCPU */
	WREG32_P(mmUVD_LMI_CTRL2, 1 << 8, ~(1 << 8));

	for (i = 0; i < 10; ++i) {
		for (j = 0; j < 100; ++j) {
			status = RREG32(mmUVD_LMI_STATUS);
			if (status & 0x240)
				break;
			mdelay(1);
		}
		if (status & 0x240)
			break;
	}

	WREG32_P(0x3D49, 0, ~(1 << 2));

	WREG32_P(mmUVD_VCPU_CNTL, 0, ~(1 << 9));

	/* put LMI, VCPU, RBC etc... into reset */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__LMI_SOFT_RESET_MASK |
		UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK |
		UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);

	WREG32(mmUVD_STATUS, 0);

	uvd_v4_2_set_dcm(adev, false);
}