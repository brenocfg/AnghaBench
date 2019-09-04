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
 unsigned long _ASCE_TYPE_REGION1 ; 
 unsigned long _REGION1_ENTRY_EMPTY ; 
 unsigned long _REGION1_INDEX ; 
 unsigned long _REGION1_SHIFT ; 
 scalar_t__ _REGION1_SIZE ; 
 unsigned long _REGION_ENTRY_ORIGIN ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __gmap_unshadow_r2t (struct gmap*,unsigned long,unsigned long*) ; 
 int __pa (unsigned long*) ; 
 int /*<<< orphan*/  gmap_call_notifier (struct gmap*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  gmap_idte_one (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 unsigned long* gmap_table_walk (struct gmap*,unsigned long,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct page* pfn_to_page (int) ; 

__attribute__((used)) static void gmap_unshadow_r2t(struct gmap *sg, unsigned long raddr)
{
	unsigned long r1o, *r1e, *r2t;
	struct page *page;

	BUG_ON(!gmap_is_shadow(sg));
	r1e = gmap_table_walk(sg, raddr, 4); /* get region-1 pointer */
	if (!r1e || !(*r1e & _REGION_ENTRY_ORIGIN))
		return;
	gmap_call_notifier(sg, raddr, raddr + _REGION1_SIZE - 1);
	r1o = (unsigned long) (r1e - ((raddr & _REGION1_INDEX) >> _REGION1_SHIFT));
	gmap_idte_one(r1o | _ASCE_TYPE_REGION1, raddr);
	r2t = (unsigned long *)(*r1e & _REGION_ENTRY_ORIGIN);
	*r1e = _REGION1_ENTRY_EMPTY;
	__gmap_unshadow_r2t(sg, raddr, r2t);
	/* Free region 2 table */
	page = pfn_to_page(__pa(r2t) >> PAGE_SHIFT);
	list_del(&page->lru);
	__free_pages(page, CRST_ALLOC_ORDER);
}