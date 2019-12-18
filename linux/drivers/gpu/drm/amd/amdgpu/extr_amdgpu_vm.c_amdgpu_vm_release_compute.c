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
struct amdgpu_vm {scalar_t__ pasid; } ;
struct TYPE_2__ {int /*<<< orphan*/  pasid_lock; int /*<<< orphan*/  pasid_idr; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void amdgpu_vm_release_compute(struct amdgpu_device *adev, struct amdgpu_vm *vm)
{
	if (vm->pasid) {
		unsigned long flags;

		spin_lock_irqsave(&adev->vm_manager.pasid_lock, flags);
		idr_remove(&adev->vm_manager.pasid_idr, vm->pasid);
		spin_unlock_irqrestore(&adev->vm_manager.pasid_lock, flags);
	}
	vm->pasid = 0;
}