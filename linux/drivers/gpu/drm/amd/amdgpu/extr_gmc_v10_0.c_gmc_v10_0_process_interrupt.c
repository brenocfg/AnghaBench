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
struct amdgpu_task_info {int /*<<< orphan*/  pid; int /*<<< orphan*/  task_name; int /*<<< orphan*/  tgid; int /*<<< orphan*/  process_name; } ;
struct amdgpu_iv_entry {size_t vmid_src; int /*<<< orphan*/  client_id; int /*<<< orphan*/  pasid; int /*<<< orphan*/  vmid; int /*<<< orphan*/  ring_id; int /*<<< orphan*/  src_id; scalar_t__* src_data; } ;
struct amdgpu_irq_src {int dummy; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; struct amdgpu_vmhub* vmhub; } ;

/* Variables and functions */
 size_t AMDGPU_GFXHUB_0 ; 
 int /*<<< orphan*/  GCVM_L2_PROTECTION_FAULT_STATUS ; 
 int /*<<< orphan*/  MAPPING_ERROR ; 
 int /*<<< orphan*/  MORE_FAULTS ; 
 int /*<<< orphan*/  PERMISSION_FAULTS ; 
 int /*<<< orphan*/  REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW ; 
 int /*<<< orphan*/  WALKER_ERROR ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vm_get_task_info (struct amdgpu_device*,int /*<<< orphan*/ ,struct amdgpu_task_info*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct amdgpu_task_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static int gmc_v10_0_process_interrupt(struct amdgpu_device *adev,
				       struct amdgpu_irq_src *source,
				       struct amdgpu_iv_entry *entry)
{
	struct amdgpu_vmhub *hub = &adev->vmhub[entry->vmid_src];
	uint32_t status = 0;
	u64 addr;

	addr = (u64)entry->src_data[0] << 12;
	addr |= ((u64)entry->src_data[1] & 0xf) << 44;

	if (!amdgpu_sriov_vf(adev)) {
		/*
		 * Issue a dummy read to wait for the status register to
		 * be updated to avoid reading an incorrect value due to
		 * the new fast GRBM interface.
		 */
		if (entry->vmid_src == AMDGPU_GFXHUB_0)
			RREG32(hub->vm_l2_pro_fault_status);

		status = RREG32(hub->vm_l2_pro_fault_status);
		WREG32_P(hub->vm_l2_pro_fault_cntl, 1, ~1);
	}

	if (printk_ratelimit()) {
		struct amdgpu_task_info task_info;

		memset(&task_info, 0, sizeof(struct amdgpu_task_info));
		amdgpu_vm_get_task_info(adev, entry->pasid, &task_info);

		dev_err(adev->dev,
			"[%s] page fault (src_id:%u ring:%u vmid:%u pasid:%u, "
			"for process %s pid %d thread %s pid %d)\n",
			entry->vmid_src ? "mmhub" : "gfxhub",
			entry->src_id, entry->ring_id, entry->vmid,
			entry->pasid, task_info.process_name, task_info.tgid,
			task_info.task_name, task_info.pid);
		dev_err(adev->dev, "  in page starting at address 0x%016llx from client %d\n",
			addr, entry->client_id);
		if (!amdgpu_sriov_vf(adev)) {
			dev_err(adev->dev,
				"GCVM_L2_PROTECTION_FAULT_STATUS:0x%08X\n",
				status);
			dev_err(adev->dev, "\t MORE_FAULTS: 0x%lx\n",
				REG_GET_FIELD(status,
				GCVM_L2_PROTECTION_FAULT_STATUS, MORE_FAULTS));
			dev_err(adev->dev, "\t WALKER_ERROR: 0x%lx\n",
				REG_GET_FIELD(status,
				GCVM_L2_PROTECTION_FAULT_STATUS, WALKER_ERROR));
			dev_err(adev->dev, "\t PERMISSION_FAULTS: 0x%lx\n",
				REG_GET_FIELD(status,
				GCVM_L2_PROTECTION_FAULT_STATUS, PERMISSION_FAULTS));
			dev_err(adev->dev, "\t MAPPING_ERROR: 0x%lx\n",
				REG_GET_FIELD(status,
				GCVM_L2_PROTECTION_FAULT_STATUS, MAPPING_ERROR));
			dev_err(adev->dev, "\t RW: 0x%lx\n",
				REG_GET_FIELD(status,
				GCVM_L2_PROTECTION_FAULT_STATUS, RW));
		}
	}

	return 0;
}