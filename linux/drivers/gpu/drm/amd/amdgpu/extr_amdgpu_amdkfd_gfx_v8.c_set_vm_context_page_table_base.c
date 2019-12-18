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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,scalar_t__) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void set_vm_context_page_table_base(struct kgd_dev *kgd, uint32_t vmid,
		uint64_t page_table_base)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);

	if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) {
		pr_err("trying to set page table base for wrong VMID\n");
		return;
	}
	WREG32(mmVM_CONTEXT8_PAGE_TABLE_BASE_ADDR + vmid - 8,
			lower_32_bits(page_table_base));
}