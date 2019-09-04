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
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_4__ {int max_pfn; } ;
struct TYPE_3__ {int prt_warning; } ;
struct amdgpu_device {TYPE_2__ vm_manager; TYPE_1__ gmc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_SHIFT ; 
 int AMDGPU_VA_RESERVED_SIZE ; 
 int /*<<< orphan*/  CB_DISABLE_READ_FAULT_ON_UNMAPPED_ACCESS ; 
 int /*<<< orphan*/  CB_DISABLE_WRITE_FAULT_ON_UNMAPPED_ACCESS ; 
 int /*<<< orphan*/  L1_TLB_STORE_INVALID_ENTRIES ; 
 int /*<<< orphan*/  L2_CACHE_STORE_INVALID_ENTRIES ; 
 int /*<<< orphan*/  MASK_PDE0_FAULT ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_DISABLE_READ_FAULT_ON_UNMAPPED_ACCESS ; 
 int /*<<< orphan*/  TC_DISABLE_WRITE_FAULT_ON_UNMAPPED_ACCESS ; 
 int /*<<< orphan*/  VM_PRT_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmVM_PRT_APERTURE0_HIGH_ADDR ; 
 int /*<<< orphan*/  mmVM_PRT_APERTURE0_LOW_ADDR ; 
 int /*<<< orphan*/  mmVM_PRT_APERTURE1_HIGH_ADDR ; 
 int /*<<< orphan*/  mmVM_PRT_APERTURE1_LOW_ADDR ; 
 int /*<<< orphan*/  mmVM_PRT_APERTURE2_HIGH_ADDR ; 
 int /*<<< orphan*/  mmVM_PRT_APERTURE2_LOW_ADDR ; 
 int /*<<< orphan*/  mmVM_PRT_APERTURE3_HIGH_ADDR ; 
 int /*<<< orphan*/  mmVM_PRT_APERTURE3_LOW_ADDR ; 
 int /*<<< orphan*/  mmVM_PRT_CNTL ; 

__attribute__((used)) static void gmc_v8_0_set_prt(struct amdgpu_device *adev, bool enable)
{
	u32 tmp;

	if (enable && !adev->gmc.prt_warning) {
		dev_warn(adev->dev, "Disabling VM faults because of PRT request!\n");
		adev->gmc.prt_warning = true;
	}

	tmp = RREG32(mmVM_PRT_CNTL);
	tmp = REG_SET_FIELD(tmp, VM_PRT_CNTL,
			    CB_DISABLE_READ_FAULT_ON_UNMAPPED_ACCESS, enable);
	tmp = REG_SET_FIELD(tmp, VM_PRT_CNTL,
			    CB_DISABLE_WRITE_FAULT_ON_UNMAPPED_ACCESS, enable);
	tmp = REG_SET_FIELD(tmp, VM_PRT_CNTL,
			    TC_DISABLE_READ_FAULT_ON_UNMAPPED_ACCESS, enable);
	tmp = REG_SET_FIELD(tmp, VM_PRT_CNTL,
			    TC_DISABLE_WRITE_FAULT_ON_UNMAPPED_ACCESS, enable);
	tmp = REG_SET_FIELD(tmp, VM_PRT_CNTL,
			    L2_CACHE_STORE_INVALID_ENTRIES, enable);
	tmp = REG_SET_FIELD(tmp, VM_PRT_CNTL,
			    L1_TLB_STORE_INVALID_ENTRIES, enable);
	tmp = REG_SET_FIELD(tmp, VM_PRT_CNTL,
			    MASK_PDE0_FAULT, enable);
	WREG32(mmVM_PRT_CNTL, tmp);

	if (enable) {
		uint32_t low = AMDGPU_VA_RESERVED_SIZE >> AMDGPU_GPU_PAGE_SHIFT;
		uint32_t high = adev->vm_manager.max_pfn -
			(AMDGPU_VA_RESERVED_SIZE >> AMDGPU_GPU_PAGE_SHIFT);

		WREG32(mmVM_PRT_APERTURE0_LOW_ADDR, low);
		WREG32(mmVM_PRT_APERTURE1_LOW_ADDR, low);
		WREG32(mmVM_PRT_APERTURE2_LOW_ADDR, low);
		WREG32(mmVM_PRT_APERTURE3_LOW_ADDR, low);
		WREG32(mmVM_PRT_APERTURE0_HIGH_ADDR, high);
		WREG32(mmVM_PRT_APERTURE1_HIGH_ADDR, high);
		WREG32(mmVM_PRT_APERTURE2_HIGH_ADDR, high);
		WREG32(mmVM_PRT_APERTURE3_HIGH_ADDR, high);
	} else {
		WREG32(mmVM_PRT_APERTURE0_LOW_ADDR, 0xfffffff);
		WREG32(mmVM_PRT_APERTURE1_LOW_ADDR, 0xfffffff);
		WREG32(mmVM_PRT_APERTURE2_LOW_ADDR, 0xfffffff);
		WREG32(mmVM_PRT_APERTURE3_LOW_ADDR, 0xfffffff);
		WREG32(mmVM_PRT_APERTURE0_HIGH_ADDR, 0x0);
		WREG32(mmVM_PRT_APERTURE1_HIGH_ADDR, 0x0);
		WREG32(mmVM_PRT_APERTURE2_HIGH_ADDR, 0x0);
		WREG32(mmVM_PRT_APERTURE3_HIGH_ADDR, 0x0);
	}
}