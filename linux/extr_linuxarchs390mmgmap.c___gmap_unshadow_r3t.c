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
struct page {int /*<<< orphan*/  lru; } ;
struct gmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CRST_ALLOC_ORDER ; 
 int PAGE_SHIFT ; 
 int _CRST_ENTRIES ; 
 unsigned long _REGION3_ENTRY_EMPTY ; 
 scalar_t__ _REGION3_SIZE ; 
 unsigned long _REGION_ENTRY_ORIGIN ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __gmap_unshadow_sgt (struct gmap*,unsigned long,unsigned long*) ; 
 int __pa (unsigned long*) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct page* pfn_to_page (int) ; 

__attribute__((used)) static void __gmap_unshadow_r3t(struct gmap *sg, unsigned long raddr,
				unsigned long *r3t)
{
	unsigned long *sgt;
	struct page *page;
	int i;

	BUG_ON(!gmap_is_shadow(sg));
	for (i = 0; i < _CRST_ENTRIES; i++, raddr += _REGION3_SIZE) {
		if (!(r3t[i] & _REGION_ENTRY_ORIGIN))
			continue;
		sgt = (unsigned long *)(r3t[i] & _REGION_ENTRY_ORIGIN);
		r3t[i] = _REGION3_ENTRY_EMPTY;
		__gmap_unshadow_sgt(sg, raddr, sgt);
		/* Free segment table */
		page = pfn_to_page(__pa(sgt) >> PAGE_SHIFT);
		list_del(&page->lru);
		__free_pages(page, CRST_ALLOC_ORDER);
	}
}