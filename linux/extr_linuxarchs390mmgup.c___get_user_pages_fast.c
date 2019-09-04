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
struct page {int dummy; } ;
struct TYPE_3__ {unsigned long asce_limit; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  gup_p4d_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,int,struct page**,int*) ; 
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
	pgd_t *pgdp, pgd;
	int nr = 0;

	start &= PAGE_MASK;
	addr = start;
	len = (unsigned long) nr_pages << PAGE_SHIFT;
	end = start + len;
	if ((end <= start) || (end > mm->context.asce_limit))
		return 0;
	/*
	 * local_irq_save() doesn't prevent pagetable teardown, but does
	 * prevent the pagetables from being freed on s390.
	 *
	 * So long as we atomically load page table pointers versus teardown,
	 * we can follow the address down to the the page and take a ref on it.
	 */
	local_irq_save(flags);
	pgdp = pgd_offset(mm, addr);
	do {
		pgd = *pgdp;
		barrier();
		next = pgd_addr_end(addr, end);
		if (pgd_none(pgd))
			break;
		if (!gup_p4d_range(pgdp, pgd, addr, next, write, pages, &nr))
			break;
	} while (pgdp++, addr = next, addr != end);
	local_irq_restore(flags);

	return nr;
}