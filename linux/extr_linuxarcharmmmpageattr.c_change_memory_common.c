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
struct page_change_data {void* clear_mask; void* set_mask; } ;
typedef  void* pgprot_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MODULES_END ; 
 int /*<<< orphan*/  MODULES_VADDR ; 
 int PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VMALLOC_END ; 
 int /*<<< orphan*/  VMALLOC_START ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int apply_to_page_range (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,struct page_change_data*) ; 
 int /*<<< orphan*/  change_page_range ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  in_range (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mm ; 

__attribute__((used)) static int change_memory_common(unsigned long addr, int numpages,
				pgprot_t set_mask, pgprot_t clear_mask)
{
	unsigned long start = addr & PAGE_MASK;
	unsigned long end = PAGE_ALIGN(addr) + numpages * PAGE_SIZE;
	unsigned long size = end - start;
	int ret;
	struct page_change_data data;

	WARN_ON_ONCE(start != addr);

	if (!size)
		return 0;

	if (!in_range(start, size, MODULES_VADDR, MODULES_END) &&
	    !in_range(start, size, VMALLOC_START, VMALLOC_END))
		return -EINVAL;

	data.set_mask = set_mask;
	data.clear_mask = clear_mask;

	ret = apply_to_page_range(&init_mm, start, size, change_page_range,
					&data);

	flush_tlb_kernel_range(start, end);
	return ret;
}