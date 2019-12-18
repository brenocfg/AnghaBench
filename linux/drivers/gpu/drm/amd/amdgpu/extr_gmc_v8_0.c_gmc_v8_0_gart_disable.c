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
typedef  scalar_t__ u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_ADVANCED_DRIVER_MODEL ; 
 int /*<<< orphan*/  ENABLE_L1_FRAGMENT_PROCESSING ; 
 int /*<<< orphan*/  ENABLE_L1_TLB ; 
 int /*<<< orphan*/  ENABLE_L2_CACHE ; 
 int /*<<< orphan*/  MC_VM_MX_L1_TLB_CNTL ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_L2_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_gart_table_vram_unpin (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmMC_VM_MX_L1_TLB_CNTL ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_CNTL ; 
 int /*<<< orphan*/  mmVM_L2_CNTL ; 
 int /*<<< orphan*/  mmVM_L2_CNTL2 ; 

__attribute__((used)) static void gmc_v8_0_gart_disable(struct amdgpu_device *adev)
{
	u32 tmp;

	/* Disable all tables */
	WREG32(mmVM_CONTEXT0_CNTL, 0);
	WREG32(mmVM_CONTEXT1_CNTL, 0);
	/* Setup TLB control */
	tmp = RREG32(mmMC_VM_MX_L1_TLB_CNTL);
	tmp = REG_SET_FIELD(tmp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_TLB, 0);
	tmp = REG_SET_FIELD(tmp, MC_VM_MX_L1_TLB_CNTL, ENABLE_L1_FRAGMENT_PROCESSING, 0);
	tmp = REG_SET_FIELD(tmp, MC_VM_MX_L1_TLB_CNTL, ENABLE_ADVANCED_DRIVER_MODEL, 0);
	WREG32(mmMC_VM_MX_L1_TLB_CNTL, tmp);
	/* Setup L2 cache */
	tmp = RREG32(mmVM_L2_CNTL);
	tmp = REG_SET_FIELD(tmp, VM_L2_CNTL, ENABLE_L2_CACHE, 0);
	WREG32(mmVM_L2_CNTL, tmp);
	WREG32(mmVM_L2_CNTL2, 0);
	amdgpu_gart_table_vram_unpin(adev);
}