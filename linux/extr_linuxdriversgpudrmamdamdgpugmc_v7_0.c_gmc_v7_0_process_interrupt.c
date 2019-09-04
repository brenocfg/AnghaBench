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
typedef  int u32 ;
struct kfd_vm_fault_info {int vmid; int status; int page_addr; int prot_valid; int prot_read; int prot_write; int prot_exec; void* mc_id; } ;
struct amdgpu_iv_entry {int /*<<< orphan*/  pasid; int /*<<< orphan*/ * src_data; int /*<<< orphan*/  src_id; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_fault_info_updated; struct kfd_vm_fault_info* vm_fault_info; } ;
struct amdgpu_device {TYPE_1__ gmc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_VM_FAULT_STOP_FIRST ; 
 int /*<<< orphan*/  MEMORY_CLIENT_ID ; 
 int /*<<< orphan*/  PROTECTIONS ; 
 void* REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMID ; 
 int /*<<< orphan*/  VM_CONTEXT1_PROTECTION_FAULT_STATUS ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ amdgpu_amdkfd_is_kfd_vmid (struct amdgpu_device*,int) ; 
 scalar_t__ amdgpu_vm_fault_stop ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gmc_v7_0_set_fault_enable_default (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gmc_v7_0_vm_decode_fault (struct amdgpu_device*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_CNTL2 ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_PROTECTION_FAULT_ADDR ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_PROTECTION_FAULT_MCCLIENT ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_PROTECTION_FAULT_STATUS ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static int gmc_v7_0_process_interrupt(struct amdgpu_device *adev,
				      struct amdgpu_irq_src *source,
				      struct amdgpu_iv_entry *entry)
{
	u32 addr, status, mc_client, vmid;

	addr = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_ADDR);
	status = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_STATUS);
	mc_client = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_MCCLIENT);
	/* reset addr and status */
	WREG32_P(mmVM_CONTEXT1_CNTL2, 1, ~1);

	if (!addr && !status)
		return 0;

	if (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_FIRST)
		gmc_v7_0_set_fault_enable_default(adev, false);

	if (printk_ratelimit()) {
		dev_err(adev->dev, "GPU fault detected: %d 0x%08x\n",
			entry->src_id, entry->src_data[0]);
		dev_err(adev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_ADDR   0x%08X\n",
			addr);
		dev_err(adev->dev, "  VM_CONTEXT1_PROTECTION_FAULT_STATUS 0x%08X\n",
			status);
		gmc_v7_0_vm_decode_fault(adev, status, addr, mc_client,
					 entry->pasid);
	}

	vmid = REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS,
			     VMID);
	if (amdgpu_amdkfd_is_kfd_vmid(adev, vmid)
		&& !atomic_read(&adev->gmc.vm_fault_info_updated)) {
		struct kfd_vm_fault_info *info = adev->gmc.vm_fault_info;
		u32 protections = REG_GET_FIELD(status,
					VM_CONTEXT1_PROTECTION_FAULT_STATUS,
					PROTECTIONS);

		info->vmid = vmid;
		info->mc_id = REG_GET_FIELD(status,
					    VM_CONTEXT1_PROTECTION_FAULT_STATUS,
					    MEMORY_CLIENT_ID);
		info->status = status;
		info->page_addr = addr;
		info->prot_valid = protections & 0x7 ? true : false;
		info->prot_read = protections & 0x8 ? true : false;
		info->prot_write = protections & 0x10 ? true : false;
		info->prot_exec = protections & 0x20 ? true : false;
		mb();
		atomic_set(&adev->gmc.vm_fault_info_updated, 1);
	}

	return 0;
}