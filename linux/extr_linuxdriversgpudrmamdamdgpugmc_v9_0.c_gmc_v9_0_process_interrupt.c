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
typedef  int u64 ;
struct amdgpu_vmhub {int /*<<< orphan*/  vm_l2_pro_fault_cntl; int /*<<< orphan*/  vm_l2_pro_fault_status; } ;
struct amdgpu_task_info {int /*<<< orphan*/  pid; int /*<<< orphan*/  task_name; int /*<<< orphan*/  tgid; int /*<<< orphan*/  process_name; int /*<<< orphan*/  member_0; } ;
struct amdgpu_iv_entry {size_t vmid_src; int /*<<< orphan*/  client_id; int /*<<< orphan*/  pasid; int /*<<< orphan*/  vmid; int /*<<< orphan*/  ring_id; int /*<<< orphan*/  src_id; scalar_t__* src_data; } ;
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; struct amdgpu_vmhub* vmhub; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vm_get_task_info (struct amdgpu_device*,int /*<<< orphan*/ ,struct amdgpu_task_info*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static int gmc_v9_0_process_interrupt(struct amdgpu_device *adev,
				struct amdgpu_irq_src *source,
				struct amdgpu_iv_entry *entry)
{
	struct amdgpu_vmhub *hub = &adev->vmhub[entry->vmid_src];
	uint32_t status = 0;
	u64 addr;

	addr = (u64)entry->src_data[0] << 12;
	addr |= ((u64)entry->src_data[1] & 0xf) << 44;

	if (!amdgpu_sriov_vf(adev)) {
		status = RREG32(hub->vm_l2_pro_fault_status);
		WREG32_P(hub->vm_l2_pro_fault_cntl, 1, ~1);
	}

	if (printk_ratelimit()) {
		struct amdgpu_task_info task_info = { 0 };

		amdgpu_vm_get_task_info(adev, entry->pasid, &task_info);

		dev_err(adev->dev,
			"[%s] VMC page fault (src_id:%u ring:%u vmid:%u pasid:%u, for process %s pid %d thread %s pid %d\n)\n",
			entry->vmid_src ? "mmhub" : "gfxhub",
			entry->src_id, entry->ring_id, entry->vmid,
			entry->pasid, task_info.process_name, task_info.tgid,
			task_info.task_name, task_info.pid);
		dev_err(adev->dev, "  at address 0x%016llx from %d\n",
			addr, entry->client_id);
		if (!amdgpu_sriov_vf(adev))
			dev_err(adev->dev,
				"VM_L2_PROTECTION_FAULT_STATUS:0x%08X\n",
				status);
	}

	return 0;
}