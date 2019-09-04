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
typedef  unsigned int uint64_t ;
struct amdgpu_vm_pt {struct amdgpu_vm_pt* entries; } ;
struct amdgpu_pte_update_params {TYPE_3__* adev; TYPE_1__* vm; } ;
struct TYPE_5__ {unsigned int root_level; } ;
struct TYPE_6__ {TYPE_2__ vm_manager; } ;
struct TYPE_4__ {struct amdgpu_vm_pt root; } ;

/* Variables and functions */
 unsigned int AMDGPU_VM_PTB ; 
 unsigned int amdgpu_vm_level_shift (TYPE_3__*,int /*<<< orphan*/ ) ; 

void amdgpu_vm_get_entry(struct amdgpu_pte_update_params *p, uint64_t addr,
			 struct amdgpu_vm_pt **entry,
			 struct amdgpu_vm_pt **parent)
{
	unsigned level = p->adev->vm_manager.root_level;

	*parent = NULL;
	*entry = &p->vm->root;
	while ((*entry)->entries) {
		unsigned shift = amdgpu_vm_level_shift(p->adev, level++);

		*parent = *entry;
		*entry = &(*entry)->entries[addr >> shift];
		addr &= (1ULL << shift) - 1;
	}

	if (level != AMDGPU_VM_PTB)
		*entry = NULL;
}