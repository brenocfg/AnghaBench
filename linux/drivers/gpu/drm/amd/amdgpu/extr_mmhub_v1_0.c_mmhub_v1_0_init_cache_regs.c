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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ translate_further; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_SELECT ; 
 int /*<<< orphan*/  CONTEXT1_IDENTITY_ACCESS_MODE ; 
 int /*<<< orphan*/  ENABLE_L2_CACHE ; 
 int /*<<< orphan*/  ENABLE_L2_FRAGMENT_PROCESSING ; 
 int /*<<< orphan*/  IDENTITY_MODE_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  INVALIDATE_ALL_L1_TLBS ; 
 int /*<<< orphan*/  INVALIDATE_L2_CACHE ; 
 int /*<<< orphan*/  L2_CACHE_BIGK_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  L2_PDE0_CACHE_TAG_GENERATION_MODE ; 
 int /*<<< orphan*/  MMHUB ; 
 int /*<<< orphan*/  PDE_FAULT_CLASSIFICATION ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMC_TAP_PDE_REQUEST_PHYSICAL ; 
 int /*<<< orphan*/  VMC_TAP_PTE_REQUEST_PHYSICAL ; 
 int /*<<< orphan*/  VM_L2_CNTL ; 
 int /*<<< orphan*/  VM_L2_CNTL2 ; 
 int /*<<< orphan*/  VM_L2_CNTL3 ; 
 int /*<<< orphan*/  VM_L2_CNTL4 ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmVM_L2_CNTL ; 
 int /*<<< orphan*/  mmVM_L2_CNTL2 ; 
 int /*<<< orphan*/  mmVM_L2_CNTL3 ; 
 int /*<<< orphan*/  mmVM_L2_CNTL4 ; 
 int /*<<< orphan*/  mmVM_L2_CNTL4_DEFAULT ; 

__attribute__((used)) static void mmhub_v1_0_init_cache_regs(struct amdgpu_device *adev)
{
	uint32_t tmp;

	if (amdgpu_sriov_vf(adev))
		return;

	/* Setup L2 cache */
	tmp = RREG32_SOC15(MMHUB, 0, mmVM_L2_CNTL);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, ENABLE_L2_CACHE, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, ENABLE_L2_FRAGMENT_PROCESSING, 1);
	/* XXX for emulation, Refer to closed source code.*/
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, L2_PDE0_CACHE_TAG_GENERATION_MODE,
			    0);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, PDE_FAULT_CLASSIFICATION, 0);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, IDENTITY_MODE_FRAGMENT_SIZE, 0);
	WREG32_SOC15(MMHUB, 0, mmVM_L2_CNTL, tmp);

	tmp = RREG32_SOC15(MMHUB, 0, mmVM_L2_CNTL2);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL2, INVALIDATE_ALL_L1_TLBS, 1);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL2, INVALIDATE_L2_CACHE, 1);
	WREG32_SOC15(MMHUB, 0, mmVM_L2_CNTL2, tmp);

	if (adev->gmc.translate_further) {
		tmp = REG_SET_FIELD(tmp, VM_L2_CNTL3, BANK_SELECT, 12);
		tmp = REG_SET_FIELD(tmp, VM_L2_CNTL3,
				    L2_CACHE_BIGK_FRAGMENT_SIZE, 9);
	} else {
		tmp = REG_SET_FIELD(tmp, VM_L2_CNTL3, BANK_SELECT, 9);
		tmp = REG_SET_FIELD(tmp, VM_L2_CNTL3,
				    L2_CACHE_BIGK_FRAGMENT_SIZE, 6);
	}
	WREG32_SOC15(MMHUB, 0, mmVM_L2_CNTL3, tmp);

	tmp = mmVM_L2_CNTL4_DEFAULT;
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL4, VMC_TAP_PDE_REQUEST_PHYSICAL, 0);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL4, VMC_TAP_PTE_REQUEST_PHYSICAL, 0);
	WREG32_SOC15(MMHUB, 0, mmVM_L2_CNTL4, tmp);
}