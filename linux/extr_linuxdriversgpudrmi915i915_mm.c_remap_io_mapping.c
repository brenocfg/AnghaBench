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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_mm; } ;
struct remap_pfn {unsigned long pfn; int /*<<< orphan*/  mm; int /*<<< orphan*/  prot; } ;
struct io_mapping {int /*<<< orphan*/  prot; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 unsigned long PAGE_SHIFT ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int _PAGE_CACHE_MASK ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int apply_to_page_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ,struct remap_pfn*) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_pfn ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zap_vma_ptes (struct vm_area_struct*,unsigned long,unsigned long) ; 

int remap_io_mapping(struct vm_area_struct *vma,
		     unsigned long addr, unsigned long pfn, unsigned long size,
		     struct io_mapping *iomap)
{
	struct remap_pfn r;
	int err;

	GEM_BUG_ON((vma->vm_flags &
		    (VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP)) !=
		   (VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP));

	/* We rely on prevalidation of the io-mapping to skip track_pfn(). */
	r.mm = vma->vm_mm;
	r.pfn = pfn;
	r.prot = __pgprot((pgprot_val(iomap->prot) & _PAGE_CACHE_MASK) |
			  (pgprot_val(vma->vm_page_prot) & ~_PAGE_CACHE_MASK));

	err = apply_to_page_range(r.mm, addr, size, remap_pfn, &r);
	if (unlikely(err)) {
		zap_vma_ptes(vma, addr, (r.pfn - pfn) << PAGE_SHIFT);
		return err;
	}

	return 0;
}