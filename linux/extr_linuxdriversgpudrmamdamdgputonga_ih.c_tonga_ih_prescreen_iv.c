#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_3__ {int rptr; int /*<<< orphan*/ * ring; } ;
struct TYPE_4__ {TYPE_1__ ih; } ;
struct amdgpu_device {TYPE_2__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_vm_pasid_fault_credit (struct amdgpu_device*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tonga_ih_prescreen_iv(struct amdgpu_device *adev)
{
	u32 ring_index = adev->irq.ih.rptr >> 2;
	u16 pasid;

	switch (le32_to_cpu(adev->irq.ih.ring[ring_index]) & 0xff) {
	case 146:
	case 147:
		pasid = le32_to_cpu(adev->irq.ih.ring[ring_index + 2]) >> 16;
		if (!pasid || amdgpu_vm_pasid_fault_credit(adev, pasid))
			return true;
		break;
	default:
		/* Not a VM fault */
		return true;
	}

	adev->irq.ih.rptr += 16;
	return false;
}