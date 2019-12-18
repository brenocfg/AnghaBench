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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;
struct amdgpu_device {TYPE_1__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PASSTHROUGH_MODE ; 
 int /*<<< orphan*/  AMDGPU_SRIOV_CAPS_ENABLE_IOV ; 
 int /*<<< orphan*/  AMDGPU_SRIOV_CAPS_IS_VF ; 
 int /*<<< orphan*/  NBIO ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_virtual_machine () ; 
 int /*<<< orphan*/  mmRCC_DEV0_EPF0_RCC_IOV_FUNC_IDENTIFIER ; 

__attribute__((used)) static void nbio_v2_3_detect_hw_virt(struct amdgpu_device *adev)
{
	uint32_t reg;

	reg = RREG32_SOC15(NBIO, 0, mmRCC_DEV0_EPF0_RCC_IOV_FUNC_IDENTIFIER);
	if (reg & 1)
		adev->virt.caps |= AMDGPU_SRIOV_CAPS_IS_VF;

	if (reg & 0x80000000)
		adev->virt.caps |= AMDGPU_SRIOV_CAPS_ENABLE_IOV;

	if (!reg) {
		if (is_virtual_machine())	/* passthrough mode exclus sriov mod */
			adev->virt.caps |= AMDGPU_PASSTHROUGH_MODE;
	}
}