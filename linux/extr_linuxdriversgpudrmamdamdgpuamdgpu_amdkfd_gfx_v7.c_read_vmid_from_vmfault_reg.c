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
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMID ; 
 int /*<<< orphan*/  VM_CONTEXT1_PROTECTION_FAULT_STATUS ; 
 struct amdgpu_device* get_amdgpu_device (struct kgd_dev*) ; 
 int /*<<< orphan*/  mmVM_CONTEXT1_PROTECTION_FAULT_STATUS ; 

__attribute__((used)) static uint32_t read_vmid_from_vmfault_reg(struct kgd_dev *kgd)
{
	struct amdgpu_device *adev = get_amdgpu_device(kgd);

	uint32_t status = RREG32(mmVM_CONTEXT1_PROTECTION_FAULT_STATUS);

	return REG_GET_FIELD(status, VM_CONTEXT1_PROTECTION_FAULT_STATUS, VMID);
}