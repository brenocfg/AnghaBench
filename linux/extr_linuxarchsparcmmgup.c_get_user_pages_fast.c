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
 int /*<<< orphan*/  FOLL_WRITE ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 TYPE_1__* current ; 
 int get_user_pages_unlocked (unsigned long,unsigned long,struct page**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gup_pud_range (int /*<<< orphan*/ ,unsigned long,unsigned long,int,struct page**,int*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 

int get_user_pages_fast(unsigned long start, int nr_pages, int write,
			struct page **pages)
{
	struct mm_struct *mm = current->mm;
	unsigned long addr, len, end;
	unsigned long next;
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
		 * ADI bits. IOMMU does not implements version tags,
		 */
		addr = (addr << (long)adi_nbits()) >> (long)adi_nbits();
		start = addr;
	}
#endif
	start &= PAGE_MASK;
	addr = start;
	len = (unsigned long) nr_pages << PAGE_SHIFT;
	end = start + len;

	/*
	 * XXX: batch / limit 'nr', to avoid large irq off latency
	 * needs some instrumenting to determine the common sizes used by
	 * important workloads (eg. DB2), and whether limiting the batch size
	 * will decrease performance.
	 *
	 * It seems like we're in the clear for the moment. Direct-IO is
	 * the main guy that batches up lots of get_user_pages, and even
	 * they are limited to 64-at-a-time which is not so many.
	 */
	/*
	 * This doesn't prevent pagetable teardown, but does prevent
	 * the pagetables from being freed on sparc.
	 *
	 * So long as we atomically load page table pointers versus teardown,
	 * we can follow the address down to the the page and take a ref on it.
	 */
	local_irq_disable();

	pgdp = pgd_offset(mm, addr);
	do {
		pgd_t pgd = *pgdp;

		next = pgd_addr_end(addr, end);
		if (pgd_none(pgd))
			goto slow;
		if (!gup_pud_range(pgd, addr, next, write, pages, &nr))
			goto slow;
	} while (pgdp++, addr = next, addr != end);

	local_irq_enable();

	VM_BUG_ON(nr != (end - start) >> PAGE_SHIFT);
	return nr;

	{
		int ret;

slow:
		local_irq_enable();

		/* Try to get the remaining pages with get_user_pages */
		start += nr << PAGE_SHIFT;
		pages += nr;

		ret = get_user_pages_unlocked(start,
			(end - start) >> PAGE_SHIFT, pages,
			write ? FOLL_WRITE : 0);

		/* Have to be a bit careful with return values */
		if (nr > 0) {
			if (ret < 0)
				ret = nr;
			else
				ret += nr;
		}

		return ret;
	}
}