#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {unsigned int num_level; unsigned int block_size; scalar_t__ max_pfn; } ;
struct TYPE_3__ {scalar_t__ translate_further; } ;
struct amdgpu_device {TYPE_2__ vm_manager; TYPE_1__ gmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  ENABLE_CONTEXT ; 
 int /*<<< orphan*/  EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  MMHUB ; 
 int /*<<< orphan*/  PAGE_TABLE_BLOCK_SIZE ; 
 int /*<<< orphan*/  PAGE_TABLE_DEPTH ; 
 int /*<<< orphan*/  PDE0_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  RANGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  READ_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RETRY_PERMISSION_OR_INVALID_PAGE_FAULT ; 
 int /*<<< orphan*/  RREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VALID_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  VM_CONTEXT1_CNTL ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  amdgpu_noretry ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_CNTL ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_PAGE_TABLE_END_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_PAGE_TABLE_END_ADDR_LO32 ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_PAGE_TABLE_START_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_PAGE_TABLE_START_ADDR_LO32 ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void mmhub_v1_0_setup_vmid_config(struct amdgpu_device *adev)
{
	unsigned num_level, block_size;
	uint32_t tmp;
	int i;

	num_level = adev->vm_manager.num_level;
	block_size = adev->vm_manager.block_size;
	if (adev->gmc.translate_further)
		num_level -= 1;
	else
		block_size -= 9;

	for (i = 0; i <= 14; i++) {
		tmp = RREG32_SOC15_OFFSET(MMHUB, 0, mmVM_CONTEXT1_CNTL, i);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL, ENABLE_CONTEXT, 1);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL, PAGE_TABLE_DEPTH,
				    num_level);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    RANGE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT,
				    1);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    PDE0_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    VALID_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    READ_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    WRITE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT, 1);
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    PAGE_TABLE_BLOCK_SIZE,
				    block_size);
		/* Send no-retry XNACK on fault to suppress VM fault storm. */
		tmp = REG_SET_FIELD(tmp, VM_CONTEXT1_CNTL,
				    RETRY_PERMISSION_OR_INVALID_PAGE_FAULT,
				    !amdgpu_noretry);
		WREG32_SOC15_OFFSET(MMHUB, 0, mmVM_CONTEXT1_CNTL, i, tmp);
		WREG32_SOC15_OFFSET(MMHUB, 0, mmVM_CONTEXT1_PAGE_TABLE_START_ADDR_LO32, i*2, 0);
		WREG32_SOC15_OFFSET(MMHUB, 0, mmVM_CONTEXT1_PAGE_TABLE_START_ADDR_HI32, i*2, 0);
		WREG32_SOC15_OFFSET(MMHUB, 0, mmVM_CONTEXT1_PAGE_TABLE_END_ADDR_LO32, i*2,
			lower_32_bits(adev->vm_manager.max_pfn - 1));
		WREG32_SOC15_OFFSET(MMHUB, 0, mmVM_CONTEXT1_PAGE_TABLE_END_ADDR_HI32, i*2,
			upper_32_bits(adev->vm_manager.max_pfn - 1));
	}
}