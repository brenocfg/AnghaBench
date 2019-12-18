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
typedef  unsigned long long uint64_t ;
struct amdgpu_vm_update_params {scalar_t__ pages_addr; TYPE_2__* adev; } ;
struct TYPE_3__ {unsigned int fragment_size; } ;
struct TYPE_4__ {scalar_t__ asic_type; TYPE_1__ vm_manager; } ;

/* Variables and functions */
 scalar_t__ CHIP_VEGA10 ; 
 scalar_t__ ffs (unsigned long long) ; 
 scalar_t__ fls64 (unsigned long long) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static void amdgpu_vm_fragment(struct amdgpu_vm_update_params *params,
			       uint64_t start, uint64_t end, uint64_t flags,
			       unsigned int *frag, uint64_t *frag_end)
{
	/**
	 * The MC L1 TLB supports variable sized pages, based on a fragment
	 * field in the PTE. When this field is set to a non-zero value, page
	 * granularity is increased from 4KB to (1 << (12 + frag)). The PTE
	 * flags are considered valid for all PTEs within the fragment range
	 * and corresponding mappings are assumed to be physically contiguous.
	 *
	 * The L1 TLB can store a single PTE for the whole fragment,
	 * significantly increasing the space available for translation
	 * caching. This leads to large improvements in throughput when the
	 * TLB is under pressure.
	 *
	 * The L2 TLB distributes small and large fragments into two
	 * asymmetric partitions. The large fragment cache is significantly
	 * larger. Thus, we try to use large fragments wherever possible.
	 * Userspace can support this by aligning virtual base address and
	 * allocation size to the fragment size.
	 *
	 * Starting with Vega10 the fragment size only controls the L1. The L2
	 * is now directly feed with small/huge/giant pages from the walker.
	 */
	unsigned max_frag;

	if (params->adev->asic_type < CHIP_VEGA10)
		max_frag = params->adev->vm_manager.fragment_size;
	else
		max_frag = 31;

	/* system pages are non continuously */
	if (params->pages_addr) {
		*frag = 0;
		*frag_end = end;
		return;
	}

	/* This intentionally wraps around if no bit is set */
	*frag = min((unsigned)ffs(start) - 1, (unsigned)fls64(end - start) - 1);
	if (*frag >= max_frag) {
		*frag = max_frag;
		*frag_end = end & ~((1ULL << max_frag) - 1);
	} else {
		*frag_end = start + (1 << *frag);
	}
}