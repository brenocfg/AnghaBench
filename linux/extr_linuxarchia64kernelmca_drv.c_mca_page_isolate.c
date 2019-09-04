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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  isolate_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISOLATE_NG ; 
 int /*<<< orphan*/  ISOLATE_NONE ; 
 int /*<<< orphan*/  ISOLATE_OK ; 
 int MAX_PAGE_ISOLATE ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PageReserved (struct page*) ; 
 scalar_t__ PageSlab (struct page*) ; 
 int /*<<< orphan*/  SetPageReserved (struct page*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  ia64_phys_addr_valid (unsigned long) ; 
 int num_page_isolate ; 
 struct page** page_isolate ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 

__attribute__((used)) static isolate_status_t
mca_page_isolate(unsigned long paddr)
{
	int i;
	struct page *p;

	/* whether physical address is valid or not */
	if (!ia64_phys_addr_valid(paddr))
		return ISOLATE_NONE;

	if (!pfn_valid(paddr >> PAGE_SHIFT))
		return ISOLATE_NONE;

	/* convert physical address to physical page number */
	p = pfn_to_page(paddr>>PAGE_SHIFT);

	/* check whether a page number have been already registered or not */
	for (i = 0; i < num_page_isolate; i++)
		if (page_isolate[i] == p)
			return ISOLATE_OK; /* already listed */

	/* limitation check */
	if (num_page_isolate == MAX_PAGE_ISOLATE)
		return ISOLATE_NG;

	/* kick pages having attribute 'SLAB' or 'Reserved' */
	if (PageSlab(p) || PageReserved(p))
		return ISOLATE_NG;

	/* add attribute 'Reserved' and register the page */
	get_page(p);
	SetPageReserved(p);
	page_isolate[num_page_isolate++] = p;

	return ISOLATE_OK;
}