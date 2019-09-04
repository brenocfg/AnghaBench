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
typedef  unsigned int uint64_t ;
struct TYPE_2__ {struct amdgpu_bo* bo; } ;
struct amdgpu_vm_pt {TYPE_1__ base; scalar_t__ huge; } ;
struct amdgpu_pte_update_params {int /*<<< orphan*/  (* func ) (struct amdgpu_pte_update_params*,struct amdgpu_bo*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ;struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo {struct amdgpu_bo* shadow; } ;

/* Variables and functions */
 unsigned int AMDGPU_GPU_PAGE_SIZE ; 
 unsigned int AMDGPU_VM_PTE_COUNT (struct amdgpu_device*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  amdgpu_vm_get_entry (struct amdgpu_pte_update_params*,unsigned int,struct amdgpu_vm_pt**,struct amdgpu_vm_pt**) ; 
 int /*<<< orphan*/  amdgpu_vm_handle_huge_pages (struct amdgpu_pte_update_params*,struct amdgpu_vm_pt*,struct amdgpu_vm_pt*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_pte_update_params*,struct amdgpu_bo*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_pte_update_params*,struct amdgpu_bo*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int amdgpu_vm_update_ptes(struct amdgpu_pte_update_params *params,
				  uint64_t start, uint64_t end,
				  uint64_t dst, uint64_t flags)
{
	struct amdgpu_device *adev = params->adev;
	const uint64_t mask = AMDGPU_VM_PTE_COUNT(adev) - 1;

	uint64_t addr, pe_start;
	struct amdgpu_bo *pt;
	unsigned nptes;

	/* walk over the address space and update the page tables */
	for (addr = start; addr < end; addr += nptes,
	     dst += nptes * AMDGPU_GPU_PAGE_SIZE) {
		struct amdgpu_vm_pt *entry, *parent;

		amdgpu_vm_get_entry(params, addr, &entry, &parent);
		if (!entry)
			return -ENOENT;

		if ((addr & ~mask) == (end & ~mask))
			nptes = end - addr;
		else
			nptes = AMDGPU_VM_PTE_COUNT(adev) - (addr & mask);

		amdgpu_vm_handle_huge_pages(params, entry, parent,
					    nptes, dst, flags);
		/* We don't need to update PTEs for huge pages */
		if (entry->huge)
			continue;

		pt = entry->base.bo;
		pe_start = (addr & mask) * 8;
		if (pt->shadow)
			params->func(params, pt->shadow, pe_start, dst, nptes,
				     AMDGPU_GPU_PAGE_SIZE, flags);
		params->func(params, pt, pe_start, dst, nptes,
			     AMDGPU_GPU_PAGE_SIZE, flags);
	}

	return 0;
}