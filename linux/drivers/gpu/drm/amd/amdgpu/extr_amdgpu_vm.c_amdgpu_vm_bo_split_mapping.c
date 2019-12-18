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
typedef  scalar_t__ uint64_t ;
struct drm_mm_node {scalar_t__ size; scalar_t__ start; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_vm {int dummy; } ;
struct TYPE_2__ {int fragment_size; scalar_t__ vram_base_offset; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ vm_manager; } ;
struct amdgpu_bo_va_mapping {scalar_t__ start; scalar_t__ flags; scalar_t__ offset; scalar_t__ last; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ AMDGPU_GPU_PAGES_IN_CPU_PAGE ; 
 scalar_t__ AMDGPU_PTE_EXECUTABLE ; 
 scalar_t__ AMDGPU_PTE_LOG ; 
 scalar_t__ AMDGPU_PTE_MTYPE_NV10_MASK ; 
 scalar_t__ AMDGPU_PTE_MTYPE_VG10_MASK ; 
 scalar_t__ AMDGPU_PTE_PRT ; 
 scalar_t__ AMDGPU_PTE_READABLE ; 
 scalar_t__ AMDGPU_PTE_SNOOPED ; 
 scalar_t__ AMDGPU_PTE_SYSTEM ; 
 scalar_t__ AMDGPU_PTE_VALID ; 
 scalar_t__ AMDGPU_PTE_WRITEABLE ; 
 scalar_t__ CHIP_NAVI10 ; 
 scalar_t__ CHIP_VEGA10 ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ S64_MAX ; 
 int amdgpu_vm_bo_update_mapping (struct amdgpu_device*,struct dma_fence*,scalar_t__*,struct amdgpu_vm*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,struct dma_fence**) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_amdgpu_vm_bo_update (struct amdgpu_bo_va_mapping*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int amdgpu_vm_bo_split_mapping(struct amdgpu_device *adev,
				      struct dma_fence *exclusive,
				      dma_addr_t *pages_addr,
				      struct amdgpu_vm *vm,
				      struct amdgpu_bo_va_mapping *mapping,
				      uint64_t flags,
				      struct amdgpu_device *bo_adev,
				      struct drm_mm_node *nodes,
				      struct dma_fence **fence)
{
	unsigned min_linear_pages = 1 << adev->vm_manager.fragment_size;
	uint64_t pfn, start = mapping->start;
	int r;

	/* normally,bo_va->flags only contians READABLE and WIRTEABLE bit go here
	 * but in case of something, we filter the flags in first place
	 */
	if (!(mapping->flags & AMDGPU_PTE_READABLE))
		flags &= ~AMDGPU_PTE_READABLE;
	if (!(mapping->flags & AMDGPU_PTE_WRITEABLE))
		flags &= ~AMDGPU_PTE_WRITEABLE;

	flags &= ~AMDGPU_PTE_EXECUTABLE;
	flags |= mapping->flags & AMDGPU_PTE_EXECUTABLE;

	if (adev->asic_type >= CHIP_NAVI10) {
		flags &= ~AMDGPU_PTE_MTYPE_NV10_MASK;
		flags |= (mapping->flags & AMDGPU_PTE_MTYPE_NV10_MASK);
	} else {
		flags &= ~AMDGPU_PTE_MTYPE_VG10_MASK;
		flags |= (mapping->flags & AMDGPU_PTE_MTYPE_VG10_MASK);
	}

	if ((mapping->flags & AMDGPU_PTE_PRT) &&
	    (adev->asic_type >= CHIP_VEGA10)) {
		flags |= AMDGPU_PTE_PRT;
		if (adev->asic_type >= CHIP_NAVI10) {
			flags |= AMDGPU_PTE_SNOOPED;
			flags |= AMDGPU_PTE_LOG;
			flags |= AMDGPU_PTE_SYSTEM;
		}
		flags &= ~AMDGPU_PTE_VALID;
	}

	trace_amdgpu_vm_bo_update(mapping);

	pfn = mapping->offset >> PAGE_SHIFT;
	if (nodes) {
		while (pfn >= nodes->size) {
			pfn -= nodes->size;
			++nodes;
		}
	}

	do {
		dma_addr_t *dma_addr = NULL;
		uint64_t max_entries;
		uint64_t addr, last;

		if (nodes) {
			addr = nodes->start << PAGE_SHIFT;
			max_entries = (nodes->size - pfn) *
				AMDGPU_GPU_PAGES_IN_CPU_PAGE;
		} else {
			addr = 0;
			max_entries = S64_MAX;
		}

		if (pages_addr) {
			uint64_t count;

			for (count = 1;
			     count < max_entries / AMDGPU_GPU_PAGES_IN_CPU_PAGE;
			     ++count) {
				uint64_t idx = pfn + count;

				if (pages_addr[idx] !=
				    (pages_addr[idx - 1] + PAGE_SIZE))
					break;
			}

			if (count < min_linear_pages) {
				addr = pfn << PAGE_SHIFT;
				dma_addr = pages_addr;
			} else {
				addr = pages_addr[pfn];
				max_entries = count * AMDGPU_GPU_PAGES_IN_CPU_PAGE;
			}

		} else if (flags & AMDGPU_PTE_VALID) {
			addr += bo_adev->vm_manager.vram_base_offset;
			addr += pfn << PAGE_SHIFT;
		}

		last = min((uint64_t)mapping->last, start + max_entries - 1);
		r = amdgpu_vm_bo_update_mapping(adev, exclusive, dma_addr, vm,
						start, last, flags, addr,
						fence);
		if (r)
			return r;

		pfn += (last - start + 1) / AMDGPU_GPU_PAGES_IN_CPU_PAGE;
		if (nodes && nodes->size == pfn) {
			pfn = 0;
			++nodes;
		}
		start = last + 1;

	} while (unlikely(start != mapping->last + 1));

	return 0;
}