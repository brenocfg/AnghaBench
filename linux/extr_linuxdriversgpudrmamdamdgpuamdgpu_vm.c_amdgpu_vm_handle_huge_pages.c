#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {TYPE_3__* bo; int /*<<< orphan*/  vm_status; } ;
struct amdgpu_vm_pt {int huge; TYPE_2__ base; struct amdgpu_vm_pt* entries; } ;
struct amdgpu_pte_update_params {int /*<<< orphan*/  (* func ) (struct amdgpu_pte_update_params*,TYPE_3__*,int,int,int,int /*<<< orphan*/ ,int) ;TYPE_5__* adev; TYPE_1__* vm; int /*<<< orphan*/  src; } ;
struct TYPE_10__ {scalar_t__ asic_type; } ;
struct TYPE_9__ {struct TYPE_9__* shadow; } ;
struct TYPE_7__ {int /*<<< orphan*/  relocated; } ;

/* Variables and functions */
 int AMDGPU_PDE_PTE ; 
 int /*<<< orphan*/  AMDGPU_VM_PDB0 ; 
 unsigned int AMDGPU_VM_PTE_COUNT (TYPE_5__*) ; 
 scalar_t__ CHIP_VEGA10 ; 
 int /*<<< orphan*/  amdgpu_gmc_get_vm_pde (TYPE_5__*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_pte_update_params*,TYPE_3__*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_pte_update_params*,TYPE_3__*,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void amdgpu_vm_handle_huge_pages(struct amdgpu_pte_update_params *p,
					struct amdgpu_vm_pt *entry,
					struct amdgpu_vm_pt *parent,
					unsigned nptes, uint64_t dst,
					uint64_t flags)
{
	uint64_t pde;

	/* In the case of a mixed PT the PDE must point to it*/
	if (p->adev->asic_type >= CHIP_VEGA10 && !p->src &&
	    nptes == AMDGPU_VM_PTE_COUNT(p->adev)) {
		/* Set the huge page flag to stop scanning at this PDE */
		flags |= AMDGPU_PDE_PTE;
	}

	if (!(flags & AMDGPU_PDE_PTE)) {
		if (entry->huge) {
			/* Add the entry to the relocated list to update it. */
			entry->huge = false;
			list_move(&entry->base.vm_status, &p->vm->relocated);
		}
		return;
	}

	entry->huge = true;
	amdgpu_gmc_get_vm_pde(p->adev, AMDGPU_VM_PDB0, &dst, &flags);

	pde = (entry - parent->entries) * 8;
	if (parent->base.bo->shadow)
		p->func(p, parent->base.bo->shadow, pde, dst, 1, 0, flags);
	p->func(p, parent->base.bo, pde, dst, 1, 0, flags);
}