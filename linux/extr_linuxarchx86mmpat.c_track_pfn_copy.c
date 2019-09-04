#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int vm_flags; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int EINVAL ; 
 int VM_PAT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __pgprot (unsigned long) ; 
 scalar_t__ follow_phys (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *) ; 
 int reserve_pfn_range (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int) ; 

int track_pfn_copy(struct vm_area_struct *vma)
{
	resource_size_t paddr;
	unsigned long prot;
	unsigned long vma_size = vma->vm_end - vma->vm_start;
	pgprot_t pgprot;

	if (vma->vm_flags & VM_PAT) {
		/*
		 * reserve the whole chunk covered by vma. We need the
		 * starting address and protection from pte.
		 */
		if (follow_phys(vma, vma->vm_start, 0, &prot, &paddr)) {
			WARN_ON_ONCE(1);
			return -EINVAL;
		}
		pgprot = __pgprot(prot);
		return reserve_pfn_range(paddr, vma_size, &pgprot, 1);
	}

	return 0;
}