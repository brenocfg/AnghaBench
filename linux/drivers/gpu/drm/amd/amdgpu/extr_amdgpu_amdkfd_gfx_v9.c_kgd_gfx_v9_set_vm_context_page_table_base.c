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
typedef  int /*<<< orphan*/  uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_ARCTURUS ; 
 int /*<<< orphan*/  amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_setup_vm_pt_regs (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmhub_v1_0_setup_vm_pt_regs (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmhub_v9_4_setup_vm_pt_regs (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

void kgd_gfx_v9_set_vm_context_page_table_base(struct kgd_dev *kgd, uint32_t vmid,
		uint64_t page_table_base)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);

	if (!amdgpu_amdkfd_is_kfd_vmid(adev, vmid)) {
		pr_err("trying to set page table base for wrong VMID %u\n",
		       vmid);
		return;
	}

	/* TODO: take advantage of per-process address space size. For
	 * now, all processes share the same address space size, like
	 * on GFX8 and older.
	 */
	if (adev->asic_type == CHIP_ARCTURUS) {
		/* Two MMHUBs */
		mmhub_v9_4_setup_vm_pt_regs(adev, 0, vmid, page_table_base);
		mmhub_v9_4_setup_vm_pt_regs(adev, 1, vmid, page_table_base);
	} else
		mmhub_v1_0_setup_vm_pt_regs(adev, vmid, page_table_base);

	gfxhub_v1_0_setup_vm_pt_regs(adev, vmid, page_table_base);
}