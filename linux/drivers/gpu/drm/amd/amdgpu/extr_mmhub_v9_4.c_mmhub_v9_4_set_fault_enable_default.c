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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRASH_ON_NO_RETRY_FAULT ; 
 int /*<<< orphan*/  CRASH_ON_RETRY_FAULT ; 
 int /*<<< orphan*/  DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  MMHUB ; 
 int MMHUB_INSTANCE_REGISTER_OFFSET ; 
 int MMHUB_NUM_INSTANCES ; 
 int /*<<< orphan*/  NACK_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  PDE0_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  PDE1_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  PDE2_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  RANGE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  READ_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRANSLATE_FURTHER_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  VALID_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  VML2PF0_VM_L2_PROTECTION_FAULT_CNTL ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_PROTECTION_FAULT_ENABLE_DEFAULT ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_PROTECTION_FAULT_CNTL ; 

void mmhub_v9_4_set_fault_enable_default(struct amdgpu_device *adev, bool value)
{
	u32 tmp;
	int i;

	for (i = 0; i < MMHUB_NUM_INSTANCES; i++) {
		tmp = RREG32_SOC15_OFFSET(MMHUB, 0,
					  mmVML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
					  i * MMHUB_INSTANCE_REGISTER_OFFSET);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    RANGE_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    PDE0_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    PDE1_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    PDE2_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp,
			    VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
			    TRANSLATE_FURTHER_PROTECTION_FAULT_ENABLE_DEFAULT,
			    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    NACK_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    VALID_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    READ_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    WRITE_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    EXECUTE_PROTECTION_FAULT_ENABLE_DEFAULT,
				    value);
		if (!value) {
			tmp = REG_SET_FIELD(tmp,
					    VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
					    CRASH_ON_NO_RETRY_FAULT, 1);
			tmp = REG_SET_FIELD(tmp,
					    VML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
					    CRASH_ON_RETRY_FAULT, 1);
		}

		WREG32_SOC15_OFFSET(MMHUB, 0,
				    mmVML2PF0_VM_L2_PROTECTION_FAULT_CNTL,
				    i * MMHUB_INSTANCE_REGISTER_OFFSET, tmp);
	}
}