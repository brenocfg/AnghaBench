#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {int vram_base_offset; } ;
struct TYPE_5__ {int vram_start; } ;
struct TYPE_4__ {int table_addr; } ;
struct amdgpu_device {TYPE_3__ vm_manager; TYPE_2__ gmc; TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32 ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void gfxhub_v1_0_init_gart_pt_regs(struct amdgpu_device *adev)
{
	uint64_t value;

	BUG_ON(adev->gart.table_addr & (~0x0000FFFFFFFFF000ULL));
	value = adev->gart.table_addr - adev->gmc.vram_start
		+ adev->vm_manager.vram_base_offset;
	value &= 0x0000FFFFFFFFF000ULL;
	value |= 0x1; /*valid bit*/

	WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32,
		     lower_32_bits(value));

	WREG32_SOC15(GC, 0, mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32,
		     upper_32_bits(value));
}