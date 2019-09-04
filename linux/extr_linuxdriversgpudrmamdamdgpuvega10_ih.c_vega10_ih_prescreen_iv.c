#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct amdgpu_vm {int /*<<< orphan*/  faults; } ;
struct TYPE_5__ {int rptr; int /*<<< orphan*/ * ring; } ;
struct TYPE_6__ {TYPE_2__ ih; } ;
struct TYPE_4__ {int /*<<< orphan*/  pasid_lock; int /*<<< orphan*/  pasid_idr; } ;
struct amdgpu_device {TYPE_3__ irq; TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int AMDGPU_VM_FAULT (int,int) ; 
#define  SOC15_IH_CLIENTID_UTCL2 129 
#define  SOC15_IH_CLIENTID_VMC 128 
 int amdgpu_ih_add_fault (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_ih_clear_fault (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_vm_pasid_fault_credit (struct amdgpu_device*,int) ; 
 struct amdgpu_vm* idr_find (int /*<<< orphan*/ *,int) ; 
 int kfifo_put (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vega10_ih_prescreen_iv(struct amdgpu_device *adev)
{
	u32 ring_index = adev->irq.ih.rptr >> 2;
	u32 dw0, dw3, dw4, dw5;
	u16 pasid;
	u64 addr, key;
	struct amdgpu_vm *vm;
	int r;

	dw0 = le32_to_cpu(adev->irq.ih.ring[ring_index + 0]);
	dw3 = le32_to_cpu(adev->irq.ih.ring[ring_index + 3]);
	dw4 = le32_to_cpu(adev->irq.ih.ring[ring_index + 4]);
	dw5 = le32_to_cpu(adev->irq.ih.ring[ring_index + 5]);

	/* Filter retry page faults, let only the first one pass. If
	 * there are too many outstanding faults, ignore them until
	 * some faults get cleared.
	 */
	switch (dw0 & 0xff) {
	case SOC15_IH_CLIENTID_VMC:
	case SOC15_IH_CLIENTID_UTCL2:
		break;
	default:
		/* Not a VM fault */
		return true;
	}

	pasid = dw3 & 0xffff;
	/* No PASID, can't identify faulting process */
	if (!pasid)
		return true;

	/* Not a retry fault, check fault credit */
	if (!(dw5 & 0x80)) {
		if (!amdgpu_vm_pasid_fault_credit(adev, pasid))
			goto ignore_iv;
		return true;
	}

	addr = ((u64)(dw5 & 0xf) << 44) | ((u64)dw4 << 12);
	key = AMDGPU_VM_FAULT(pasid, addr);
	r = amdgpu_ih_add_fault(adev, key);

	/* Hash table is full or the fault is already being processed,
	 * ignore further page faults
	 */
	if (r != 0)
		goto ignore_iv;

	/* Track retry faults in per-VM fault FIFO. */
	spin_lock(&adev->vm_manager.pasid_lock);
	vm = idr_find(&adev->vm_manager.pasid_idr, pasid);
	if (!vm) {
		/* VM not found, process it normally */
		spin_unlock(&adev->vm_manager.pasid_lock);
		amdgpu_ih_clear_fault(adev, key);
		return true;
	}
	/* No locking required with single writer and single reader */
	r = kfifo_put(&vm->faults, key);
	if (!r) {
		/* FIFO is full. Ignore it until there is space */
		spin_unlock(&adev->vm_manager.pasid_lock);
		amdgpu_ih_clear_fault(adev, key);
		goto ignore_iv;
	}
	spin_unlock(&adev->vm_manager.pasid_lock);

	/* It's the first fault for this address, process it normally */
	return true;

ignore_iv:
	adev->irq.ih.rptr += 32;
	return false;
}