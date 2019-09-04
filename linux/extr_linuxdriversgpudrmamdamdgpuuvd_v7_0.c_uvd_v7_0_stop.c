#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int num_uvd_inst; int harvest_config; } ;
struct amdgpu_device {TYPE_1__ uvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  UVD_LMI_CTRL2__STALL_ARB_UMC_MASK ; 
 int UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_RBC_RB_CNTL ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_VCPU_CNTL ; 

__attribute__((used)) static void uvd_v7_0_stop(struct amdgpu_device *adev)
{
	uint8_t i = 0;

	for (i = 0; i < adev->uvd.num_uvd_inst; ++i) {
		if (adev->uvd.harvest_config & (1 << i))
			continue;
		/* force RBC into idle state */
		WREG32_SOC15(UVD, i, mmUVD_RBC_RB_CNTL, 0x11010101);

		/* Stall UMC and register bus before resetting VCPU */
		WREG32_P(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL2),
				UVD_LMI_CTRL2__STALL_ARB_UMC_MASK,
				~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);
		mdelay(1);

		/* put VCPU into reset */
		WREG32_SOC15(UVD, i, mmUVD_SOFT_RESET,
				UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(5);

		/* disable VCPU clock */
		WREG32_SOC15(UVD, i, mmUVD_VCPU_CNTL, 0x0);

		/* Unstall UMC and register bus */
		WREG32_P(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL2), 0,
				~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);
	}
}