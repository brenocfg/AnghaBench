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
struct amdgpu_pte_update_params {scalar_t__ src; TYPE_2__* adev; } ;
struct TYPE_3__ {unsigned int fragment_size; } ;
struct TYPE_4__ {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 unsigned long long AMDGPU_GPU_PAGE_SIZE ; 
 unsigned long long AMDGPU_PTE_FRAG (unsigned int) ; 
 unsigned long long AMDGPU_PTE_VALID ; 
 int amdgpu_vm_update_ptes (struct amdgpu_pte_update_params*,unsigned long long,unsigned long long,unsigned long long,unsigned long long) ; 
 scalar_t__ ffs (unsigned long long) ; 
 scalar_t__ fls64 (unsigned long long) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int amdgpu_vm_frag_ptes(struct amdgpu_pte_update_params	*params,
				uint64_t start, uint64_t end,
				uint64_t dst, uint64_t flags)
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
	 */
	unsigned max_frag = params->adev->vm_manager.fragment_size;
	int r;

	/* system pages are non continuously */
	if (params->src || !(flags & AMDGPU_PTE_VALID))
		return amdgpu_vm_update_ptes(params, start, end, dst, flags);

	while (start != end) {
		uint64_t frag_flags, frag_end;
		unsigned frag;

		/* This intentionally wraps around if no bit is set */
		frag = min((unsigned)ffs(start) - 1,
			   (unsigned)fls64(end - start) - 1);
		if (frag >= max_frag) {
			frag_flags = AMDGPU_PTE_FRAG(max_frag);
			frag_end = end & ~((1ULL << max_frag) - 1);
		} else {
			frag_flags = AMDGPU_PTE_FRAG(frag);
			frag_end = start + (1 << frag);
		}

		r = amdgpu_vm_update_ptes(params, start, frag_end, dst,
					  flags | frag_flags);
		if (r)
			return r;

		dst += (frag_end - start) * AMDGPU_GPU_PAGE_SIZE;
		start = frag_end;
	}

	return 0;
}