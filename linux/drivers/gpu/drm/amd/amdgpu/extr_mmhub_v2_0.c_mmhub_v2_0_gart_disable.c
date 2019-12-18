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
 int /*<<< orphan*/  MMMC_VM_MX_L1_TLB_CNTL ; 
 int /*<<< orphan*/  MMVM_L2_CNTL ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMMMC_VM_MX_L1_TLB_CNTL ; 
 int /*<<< orphan*/  mmMMVM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  mmMMVM_L2_CNTL ; 
 int /*<<< orphan*/  mmMMVM_L2_CNTL3 ; 

void mmhub_v2_0_gart_disable(struct amdgpu_device *adev)
{
	u32 tmp;
	u32 i;

	/* Disable all tables */
	for (i = 0; i < 16; i++)
		WREG32_SOC15_OFFSET(MMHUB, 0, mmMMVM_CONTEXT0_CNTL, i, 0);

	/* Setup TLB control */
	tmp = RREG32_SOC15(MMHUB, 0, mmMMMC_VM_MX_L1_TLB_CNTL);
	tmp = REG_SET_FIELD(tmp, MMMC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 0);
	tmp = REG_SET_FIELD(tmp, MMMC_VM_MX_L1_TLB_CNTL,
			    ENABLE_ADVANCED_DRIVER_MODEL, 0);
	WREG32_SOC15(MMHUB, 0, mmMMMC_VM_MX_L1_TLB_CNTL, tmp);

	/* Setup L2 cache */
	tmp = RREG32_SOC15(MMHUB, 0, mmMMVM_L2_CNTL);
	tmp = REG_SET_FIELD(tmp, MMVM_L2_CNTL, ENABLE_L2_CACHE, 0);
	WREG32_SOC15(MMHUB, 0, mmMMVM_L2_CNTL, tmp);
	WREG32_SOC15(MMHUB, 0, mmMMVM_L2_CNTL3, 0);
}