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
typedef  unsigned long u64 ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int cxl_handle_mm_fault (struct mm_struct*,unsigned long,unsigned long) ; 
 int get_vma_info (struct mm_struct*,unsigned long,unsigned long*,unsigned long*,unsigned long*) ; 

int cxllib_handle_fault(struct mm_struct *mm, u64 addr, u64 size, u64 flags)
{
	int rc;
	u64 dar, vma_start, vma_end;
	unsigned long page_size;

	if (mm == NULL)
		return -EFAULT;

	/*
	 * The buffer we have to process can extend over several pages
	 * and may also cover several VMAs.
	 * We iterate over all the pages. The page size could vary
	 * between VMAs.
	 */
	rc = get_vma_info(mm, addr, &vma_start, &vma_end, &page_size);
	if (rc)
		return rc;

	for (dar = (addr & ~(page_size - 1)); dar < (addr + size);
	     dar += page_size) {
		if (dar < vma_start || dar >= vma_end) {
			/*
			 * We don't hold the mm->mmap_sem semaphore
			 * while iterating, since the semaphore is
			 * required by one of the lower-level page
			 * fault processing functions and it could
			 * create a deadlock.
			 *
			 * It means the VMAs can be altered between 2
			 * loop iterations and we could theoretically
			 * miss a page (however unlikely). But that's
			 * not really a problem, as the driver will
			 * retry access, get another page fault on the
			 * missing page and call us again.
			 */
			rc = get_vma_info(mm, dar, &vma_start, &vma_end,
					&page_size);
			if (rc)
				return rc;
		}

		rc = cxl_handle_mm_fault(mm, flags, dar);
		if (rc)
			return -EFAULT;
	}
	return 0;
}