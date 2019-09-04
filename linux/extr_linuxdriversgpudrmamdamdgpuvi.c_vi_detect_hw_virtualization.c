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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PASSTHROUGH_MODE ; 
 int /*<<< orphan*/  AMDGPU_SRIOV_CAPS_ENABLE_IOV ; 
 int /*<<< orphan*/  AMDGPU_SRIOV_CAPS_IS_VF ; 
 int /*<<< orphan*/  BIF_IOV_FUNC_IDENTIFIER ; 
 scalar_t__ CHIP_FIJI ; 
 scalar_t__ CHIP_TONGA ; 
 int /*<<< orphan*/  FUNC_IDENTIFIER ; 
 int /*<<< orphan*/  IOV_ENABLE ; 
 scalar_t__ REG_GET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_virtual_machine () ; 
 int /*<<< orphan*/  mmBIF_IOV_FUNC_IDENTIFIER ; 

__attribute__((used)) static void vi_detect_hw_virtualization(struct amdgpu_device *adev)
{
	uint32_t reg = 0;

	if (adev->asic_type == CHIP_TONGA ||
	    adev->asic_type == CHIP_FIJI) {
	       reg = RREG32(mmBIF_IOV_FUNC_IDENTIFIER);
	       /* bit0: 0 means pf and 1 means vf */
	       if (REG_GET_FIELD(reg, BIF_IOV_FUNC_IDENTIFIER, FUNC_IDENTIFIER))
		       adev->virt.caps |= AMDGPU_SRIOV_CAPS_IS_VF;
	       /* bit31: 0 means disable IOV and 1 means enable */
	       if (REG_GET_FIELD(reg, BIF_IOV_FUNC_IDENTIFIER, IOV_ENABLE))
		       adev->virt.caps |= AMDGPU_SRIOV_CAPS_ENABLE_IOV;
	}

	if (reg == 0) {
		if (is_virtual_machine()) /* passthrough mode exclus sr-iov mode */
			adev->virt.caps |= AMDGPU_PASSTHROUGH_MODE;
	}
}