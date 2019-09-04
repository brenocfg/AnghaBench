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
struct TYPE_3__ {TYPE_2__* bo; int /*<<< orphan*/  vm_status; int /*<<< orphan*/  bo_list; } ;
struct amdgpu_vm_pt {struct amdgpu_vm_pt* entries; TYPE_1__ base; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_unref (TYPE_2__**) ; 
 unsigned int amdgpu_vm_num_entries (struct amdgpu_device*,unsigned int) ; 
 int /*<<< orphan*/  kvfree (struct amdgpu_vm_pt*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_vm_free_levels(struct amdgpu_device *adev,
				  struct amdgpu_vm_pt *parent,
				  unsigned level)
{
	unsigned i, num_entries = amdgpu_vm_num_entries(adev, level);

	if (parent->base.bo) {
		list_del(&parent->base.bo_list);
		list_del(&parent->base.vm_status);
		amdgpu_bo_unref(&parent->base.bo->shadow);
		amdgpu_bo_unref(&parent->base.bo);
	}

	if (parent->entries)
		for (i = 0; i < num_entries; i++)
			amdgpu_vm_free_levels(adev, &parent->entries[i],
					      level + 1);

	kvfree(parent->entries);
}