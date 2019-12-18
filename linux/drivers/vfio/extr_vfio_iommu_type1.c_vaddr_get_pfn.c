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
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_pgoff; } ;
struct page {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 unsigned int FOLL_LONGTERM ; 
 unsigned int FOLL_WRITE ; 
 int IOMMU_WRITE ; 
 unsigned long PAGE_SHIFT ; 
 int VM_PFNMAP ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma_intersection (struct mm_struct*,unsigned long,unsigned long) ; 
 int get_user_pages (unsigned long,int,unsigned int,struct page**,struct vm_area_struct**) ; 
 int get_user_pages_remote (int /*<<< orphan*/ *,struct mm_struct*,unsigned long,int,unsigned int,struct page**,struct vm_area_struct**,int /*<<< orphan*/ *) ; 
 scalar_t__ is_invalid_reserved_pfn (unsigned long) ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 unsigned long untagged_addr (unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 scalar_t__ vma_is_fsdax (struct vm_area_struct*) ; 

__attribute__((used)) static int vaddr_get_pfn(struct mm_struct *mm, unsigned long vaddr,
			 int prot, unsigned long *pfn)
{
	struct page *page[1];
	struct vm_area_struct *vma;
	struct vm_area_struct *vmas[1];
	unsigned int flags = 0;
	int ret;

	if (prot & IOMMU_WRITE)
		flags |= FOLL_WRITE;

	down_read(&mm->mmap_sem);
	if (mm == current->mm) {
		ret = get_user_pages(vaddr, 1, flags | FOLL_LONGTERM, page,
				     vmas);
	} else {
		ret = get_user_pages_remote(NULL, mm, vaddr, 1, flags, page,
					    vmas, NULL);
		/*
		 * The lifetime of a vaddr_get_pfn() page pin is
		 * userspace-controlled. In the fs-dax case this could
		 * lead to indefinite stalls in filesystem operations.
		 * Disallow attempts to pin fs-dax pages via this
		 * interface.
		 */
		if (ret > 0 && vma_is_fsdax(vmas[0])) {
			ret = -EOPNOTSUPP;
			put_page(page[0]);
		}
	}
	up_read(&mm->mmap_sem);

	if (ret == 1) {
		*pfn = page_to_pfn(page[0]);
		return 0;
	}

	down_read(&mm->mmap_sem);

	vaddr = untagged_addr(vaddr);

	vma = find_vma_intersection(mm, vaddr, vaddr + 1);

	if (vma && vma->vm_flags & VM_PFNMAP) {
		*pfn = ((vaddr - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;
		if (is_invalid_reserved_pfn(*pfn))
			ret = 0;
	}

	up_read(&mm->mmap_sem);
	return ret;
}