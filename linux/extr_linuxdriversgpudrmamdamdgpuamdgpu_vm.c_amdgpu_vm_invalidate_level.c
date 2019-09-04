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
struct TYPE_2__ {int /*<<< orphan*/  vm_status; int /*<<< orphan*/  moved; int /*<<< orphan*/  bo; } ;
struct amdgpu_vm_pt {TYPE_1__ base; struct amdgpu_vm_pt* entries; } ;
struct amdgpu_vm {int /*<<< orphan*/  relocated; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 unsigned int amdgpu_vm_num_entries (struct amdgpu_device*,unsigned int) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_vm_invalidate_level(struct amdgpu_device *adev,
				       struct amdgpu_vm *vm,
				       struct amdgpu_vm_pt *parent,
				       unsigned level)
{
	unsigned pt_idx, num_entries;

	/*
	 * Recurse into the subdirectories. This recursion is harmless because
	 * we only have a maximum of 5 layers.
	 */
	num_entries = amdgpu_vm_num_entries(adev, level);
	for (pt_idx = 0; pt_idx < num_entries; ++pt_idx) {
		struct amdgpu_vm_pt *entry = &parent->entries[pt_idx];

		if (!entry->base.bo)
			continue;

		if (!entry->base.moved)
			list_move(&entry->base.vm_status, &vm->relocated);
		amdgpu_vm_invalidate_level(adev, vm, entry, level + 1);
	}
}