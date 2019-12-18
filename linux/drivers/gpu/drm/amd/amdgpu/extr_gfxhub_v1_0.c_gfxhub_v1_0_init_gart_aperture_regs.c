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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int gart_start; int gart_end; } ;
struct TYPE_4__ {int /*<<< orphan*/  bo; } ;
struct amdgpu_device {TYPE_1__ gmc; TYPE_2__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_gmc_pd_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfxhub_v1_0_setup_vm_pt_regs (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32 ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32 ; 

__attribute__((used)) static void gfxhub_v1_0_init_gart_aperture_regs(struct amdgpu_device *adev)
{
	uint64_t pt_base = amdgpu_gmc_pd_addr(adev->gart.bo);

	gfxhub_v1_0_setup_vm_pt_regs(adev, 0, pt_base);

	WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32,
		     (u32)(adev->gmc.gart_start >> 12));
	WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32,
		     (u32)(adev->gmc.gart_start >> 44));

	WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32,
		     (u32)(adev->gmc.gart_end >> 12));
	WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32,
		     (u32)(adev->gmc.gart_end >> 44));
}