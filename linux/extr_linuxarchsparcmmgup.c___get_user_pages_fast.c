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
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gup_pud_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int,struct page**,int*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 

int __get_user_pages_fast(unsigned long start, int nr_pages, int write,
			  struct page **pages)
{
	struct mm_struct *mm = current->mm;
	unsigned long addr, len, end;
	unsigned long next, flags;
	pgd_t *pgdp;
	int nr = 0;

#ifdef CONFIG_SPARC64
	if (adi_capable()) {
		long addr = start;

		/* If userspace has passed a versioned address, kernel
		 * will not find it in the VMAs since it does not store
		 * the version tags in the list of VMAs. Storing version
		 * tags in list of VMAs is impractical since they can be
		 * changed any time from userspace without dropping into
		 * kernel. Any address search in VMAs will be done with
		 * non-versioned addresses. Ensure the ADI version bits
		 * are dropped here by sign extending the last bit before
		 * ADI bits. IOMMU does not implement version tags.
		 */
		addr = (addr << (long)adi_nbits()) >> (long)adi_nbits();
		start = addr;
	}
#endif
	start &= PAGE_MASK;
	addr = start;
	len = (unsigned long) nr_pages << PAGE_SHIFT;
	end = start + len;

	local_irq_save(flags);
	pgdp = pgd_offset(mm, addr);
	do {
		pgd_t pgd = *pgdp;

		next = pgd_addr_end(addr, end);
		if (pgd_none(pgd))
			break;
		if (!gup_pud_range(pgd, addr, next, write, pages, &nr))
			break;
	} while (pgdp++, addr = next, addr != end);
	local_irq_restore(flags);

	return nr;
}