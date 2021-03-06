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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATC_EN ; 
 int /*<<< orphan*/  ECO_BITS ; 
 int /*<<< orphan*/  ENABLE_ADVANCED_DRIVER_MODEL ; 
 int /*<<< orphan*/  ENABLE_L1_TLB ; 
 int /*<<< orphan*/  MMHUB ; 
 int MMHUB_INSTANCE_REGISTER_OFFSET ; 
 int /*<<< orphan*/  MTYPE ; 
 int MTYPE_UC ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYSTEM_ACCESS_MODE ; 
 int /*<<< orphan*/  SYSTEM_APERTURE_UNMAPPED_ACCESS ; 
 int /*<<< orphan*/  VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL ; 
 int /*<<< orphan*/  WREG32_SOC15_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmVMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL ; 

__attribute__((used)) static void mmhub_v9_4_init_tlb_regs(struct amdgpu_device *adev, int hubid)
{
	uint32_t tmp;

	/* Setup TLB control */
	tmp = RREG32_SOC15_OFFSET(MMHUB, 0,
			   mmVMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			   hubid * MMHUB_INSTANCE_REGISTER_OFFSET);

	tmp = REG_SET_FIELD(tmp, VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			    ENABLE_L1_TLB, 1);
	tmp = REG_SET_FIELD(tmp, VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			    SYSTEM_ACCESS_MODE, 3);
	tmp = REG_SET_FIELD(tmp, VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			    ENABLE_ADVANCED_DRIVER_MODEL, 1);
	tmp = REG_SET_FIELD(tmp, VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			    SYSTEM_APERTURE_UNMAPPED_ACCESS, 0);
	tmp = REG_SET_FIELD(tmp, VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			    ECO_BITS, 0);
	tmp = REG_SET_FIELD(tmp, VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			    MTYPE, MTYPE_UC);/* XXX for emulation. */
	tmp = REG_SET_FIELD(tmp, VMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			    ATC_EN, 1);

	WREG32_SOC15_OFFSET(MMHUB, 0, mmVMSHAREDVC0_MC_VM_MX_L1_TLB_CNTL,
			    hubid * MMHUB_INSTANCE_REGISTER_OFFSET, tmp);
}