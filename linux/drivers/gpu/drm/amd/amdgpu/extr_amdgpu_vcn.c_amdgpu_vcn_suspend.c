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
struct TYPE_4__ {int num_vcn_inst; int harvest_config; TYPE_1__* inst; int /*<<< orphan*/  idle_work; } ;
struct amdgpu_device {TYPE_2__ vcn; } ;
struct TYPE_3__ {int /*<<< orphan*/  saved_bo; void* cpu_addr; int /*<<< orphan*/ * vcpu_bo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int amdgpu_bo_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,void*,unsigned int) ; 

int amdgpu_vcn_suspend(struct amdgpu_device *adev)
{
	unsigned size;
	void *ptr;
	int i;

	cancel_delayed_work_sync(&adev->vcn.idle_work);

	for (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.harvest_config & (1 << i))
			continue;
		if (adev->vcn.inst[i].vcpu_bo == NULL)
			return 0;

		size = amdgpu_bo_size(adev->vcn.inst[i].vcpu_bo);
		ptr = adev->vcn.inst[i].cpu_addr;

		adev->vcn.inst[i].saved_bo = kvmalloc(size, GFP_KERNEL);
		if (!adev->vcn.inst[i].saved_bo)
			return -ENOMEM;

		memcpy_fromio(adev->vcn.inst[i].saved_bo, ptr, size);
	}
	return 0;
}