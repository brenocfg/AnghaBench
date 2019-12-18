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
struct amdgpu_vmhub {void* vm_l2_pro_fault_cntl; void* vm_l2_pro_fault_status; void* vm_context0_cntl; void* vm_inv_eng0_ack; void* vm_inv_eng0_req; void* ctx0_ptb_addr_hi32; void* ctx0_ptb_addr_lo32; } ;
struct amdgpu_device {struct amdgpu_vmhub* vmhub; } ;

/* Variables and functions */
 size_t AMDGPU_GFXHUB_0 ; 
 int /*<<< orphan*/  GC ; 
 void* SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_CNTL ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32 ; 
 int /*<<< orphan*/  mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32 ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_ENG0_ACK ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_ENG0_REQ ; 
 int /*<<< orphan*/  mmVM_L2_PROTECTION_FAULT_CNTL ; 
 int /*<<< orphan*/  mmVM_L2_PROTECTION_FAULT_STATUS ; 

void gfxhub_v1_0_init(struct amdgpu_device *adev)
{
	struct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB_0];

	hub->ctx0_ptb_addr_lo32 =
		SOC15_REG_OFFSET(GC, 0,
				 mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32);
	hub->ctx0_ptb_addr_hi32 =
		SOC15_REG_OFFSET(GC, 0,
				 mmVM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32);
	hub->vm_inv_eng0_req =
		SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG0_REQ);
	hub->vm_inv_eng0_ack =
		SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG0_ACK);
	hub->vm_context0_cntl =
		SOC15_REG_OFFSET(GC, 0, mmVM_CONTEXT0_CNTL);
	hub->vm_l2_pro_fault_status =
		SOC15_REG_OFFSET(GC, 0, mmVM_L2_PROTECTION_FAULT_STATUS);
	hub->vm_l2_pro_fault_cntl =
		SOC15_REG_OFFSET(GC, 0, mmVM_L2_PROTECTION_FAULT_CNTL);
}