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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct kgd_dev {int dummy; } ;
struct TYPE_2__ {int max_pfn; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int AMDGPU_PTE_VALID ; 
 int /*<<< orphan*/  GC ; 
 scalar_t__ SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,int) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32 ; 
 int /*<<< orphan*/  mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32 ; 
 int /*<<< orphan*/  mmGCVM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32 ; 
 int /*<<< orphan*/  mmGCVM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32 ; 
 int /*<<< orphan*/  mmGCVM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32 ; 
 int /*<<< orphan*/  mmGCVM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32 ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void set_vm_context_page_table_base(struct kgd_dev *kgd, uint32_t vmid,
		uint64_t page_table_base)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);
	uint64_t base = page_table_base | AMDGPU_PTE_VALID;

	if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) {
		pr_err("trying to set page table base for wrong VMID %u\n",
		       vmid);
		return;
	}

	/* TODO: take advantage of per-process address space size. For
	 * now, all processes share the same address space size, like
	 * on GFX8 and older.
	 */
	WREG32(SOC15_REG_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32) + (vmid*2), 0);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32) + (vmid*2), 0);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32) + (vmid*2),
			lower_32_bits(adev->vm_manager.max_pfn - 1));
	WREG32(SOC15_REG_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32) + (vmid*2),
			upper_32_bits(adev->vm_manager.max_pfn - 1));

	WREG32(SOC15_REG_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32) + (vmid*2), lower_32_bits(base));
	WREG32(SOC15_REG_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32) + (vmid*2), upper_32_bits(base));
}