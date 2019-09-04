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
struct amdgpu_vmid_mgr {unsigned int num_ids; } ;
struct TYPE_2__ {struct amdgpu_vmid_mgr* id_mgr; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 unsigned int AMDGPU_MAX_VMHUBS ; 
 int /*<<< orphan*/  amdgpu_vmid_reset (struct amdgpu_device*,unsigned int,unsigned int) ; 

void amdgpu_vmid_reset_all(struct amdgpu_device *adev)
{
	unsigned i, j;

	for (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) {
		struct amdgpu_vmid_mgr *id_mgr =
			&adev->vm_manager.id_mgr[i];

		for (j = 1; j < id_mgr->num_ids; ++j)
			amdgpu_vmid_reset(adev, i, j);
	}
}