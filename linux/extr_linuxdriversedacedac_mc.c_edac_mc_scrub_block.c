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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  edac_atomic_scrub (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 

__attribute__((used)) static void edac_mc_scrub_block(unsigned long page, unsigned long offset,
				u32 size)
{
	struct page *pg;
	void *virt_addr;
	unsigned long flags = 0;

	edac_dbg(3, "\n");

	/* ECC error page was not in our memory. Ignore it. */
	if (!pfn_valid(page))
		return;

	/* Find the actual page structure then map it and fix */
	pg = pfn_to_page(page);

	if (PageHighMem(pg))
		local_irq_save(flags);

	virt_addr = kmap_atomic(pg);

	/* Perform architecture specific atomic scrub operation */
	edac_atomic_scrub(virt_addr + offset, size);

	/* Unmap and complete */
	kunmap_atomic(virt_addr);

	if (PageHighMem(pg))
		local_irq_restore(flags);
}