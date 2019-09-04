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
struct amdgpu_vm {int /*<<< orphan*/  fault_credit; } ;
struct TYPE_2__ {int /*<<< orphan*/  pasid_lock; int /*<<< orphan*/  pasid_idr; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 struct amdgpu_vm* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool amdgpu_vm_pasid_fault_credit(struct amdgpu_device *adev,
				  unsigned int pasid)
{
	struct amdgpu_vm *vm;

	spin_lock(&adev->vm_manager.pasid_lock);
	vm = idr_find(&adev->vm_manager.pasid_idr, pasid);
	if (!vm) {
		/* VM not found, can't track fault credit */
		spin_unlock(&adev->vm_manager.pasid_lock);
		return true;
	}

	/* No lock needed. only accessed by IRQ handler */
	if (!vm->fault_credit) {
		/* Too many faults in this VM */
		spin_unlock(&adev->vm_manager.pasid_lock);
		return false;
	}

	vm->fault_credit--;
	spin_unlock(&adev->vm_manager.pasid_lock);
	return true;
}