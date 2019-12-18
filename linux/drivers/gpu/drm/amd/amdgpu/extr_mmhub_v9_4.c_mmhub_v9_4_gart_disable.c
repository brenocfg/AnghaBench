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
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_ADVANCED_DRIVER_MODEL ; 
 int /*<<< orphan*/  ENABLE_L1_TLB ; 
 int /*<<< orphan*/  ENABLE_L2_CACHE ; 
 int /*<<< orphan*/  MMHUB ; 
 int MMHUB_INSTANCE_REGISTER_OFFSET ; 
 int MMHUB_NUM_INSTANCES ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VML2PF0_VM_L2_CNTL ; 
 int /*<<< orphan*/  VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_CNTL ; 
 int /*<<< orphan*/  mmVML2PF0_VM_L2_CNTL3 ; 
 int /*<<< orphan*/  mmVML2VC0_VM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  mmVMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL ; 

void mmhub_v9_4_gart_disable(struct amdgpu_device *adev)
{
	u32 tmp;
	u32 i, j;

	for (j = 0; j < MMHUB_NUM_INSTANCES; j++) {
		/* Disable all tables */
		for (i = 0; i < 16; i++)
			WREG32_SOC15_OFFSET(MMHUB, 0,
					    mmVML2VC0_VM_CONTEXT0_CNTL,
					    j * MMHUB_INSTANCE_REGISTER_OFFSET +
					    i, 0);

		/* Setup TLB control */
		tmp = RREG32_SOC15_OFFSET(MMHUB, 0,
				   mmVMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
				   j * MMHUB_INSTANCE_REGISTER_OFFSET);
		tmp = REG_SET_FIELD(tmp, VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
				    ENABLE_L1_TLB, 0);
		tmp = REG_SET_FIELD(tmp,
				    VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
				    ENABLE_ADVANCED_DRIVER_MODEL, 0);
		WREG32_SOC15_OFFSET(MMHUB, 0,
				    mmVMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
				    j * MMHUB_INSTANCE_REGISTER_OFFSET, tmp);

		/* Setup L2 cache */
		tmp = RREG32_SOC15_OFFSET(MMHUB, 0, mmVML2PF0_VM_L2_CNTL,
					  j * MMHUB_INSTANCE_REGISTER_OFFSET);
		tmp = REG_SET_FIELD(tmp, VML2PF0_VM_L2_CNTL,
				    ENABLE_L2_CACHE, 0);
		WREG32_SOC15_OFFSET(MMHUB, 0, mmVML2PF0_VM_L2_CNTL,
				    j * MMHUB_INSTANCE_REGISTER_OFFSET, tmp);
		WREG32_SOC15_OFFSET(MMHUB, 0, mmVML2PF0_VM_L2_CNTL3,
				    j * MMHUB_INSTANCE_REGISTER_OFFSET, 0);
	}
}