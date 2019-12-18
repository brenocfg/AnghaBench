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
struct TYPE_4__ {int max_handles; int num_uvd_inst; int harvest_config; TYPE_1__* inst; int /*<<< orphan*/ * handles; int /*<<< orphan*/  idle_work; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_2__ uvd; } ;
struct TYPE_3__ {int /*<<< orphan*/  saved_bo; void* cpu_addr; int /*<<< orphan*/ * vcpu_bo; } ;

/* Variables and functions */
 scalar_t__ CHIP_POLARIS10 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int amdgpu_bo_size (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,void*,unsigned int) ; 

int amdgpu_uvd_suspend(struct amdgpu_device *adev)
{
	unsigned size;
	void *ptr;
	int i, j;

	cancel_delayed_work_sync(&adev->uvd.idle_work);

	/* only valid for physical mode */
	if (adev->asic_type < CHIP_POLARIS10) {
		for (i = 0; i < adev->uvd.max_handles; ++i)
			if (atomic_read(&adev->uvd.handles[i]))
				break;

		if (i == adev->uvd.max_handles)
			return 0;
	}

	for (j = 0; j < adev->uvd.num_uvd_inst; ++j) {
		if (adev->uvd.harvest_config & (1 << j))
			continue;
		if (adev->uvd.inst[j].vcpu_bo == NULL)
			continue;

		size = amdgpu_bo_size(adev->uvd.inst[j].vcpu_bo);
		ptr = adev->uvd.inst[j].cpu_addr;

		adev->uvd.inst[j].saved_bo = kvmalloc(size, GFP_KERNEL);
		if (!adev->uvd.inst[j].saved_bo)
			return -ENOMEM;

		memcpy_fromio(adev->uvd.inst[j].saved_bo, ptr, size);
	}
	return 0;
}