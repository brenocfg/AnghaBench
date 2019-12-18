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
struct pagevec {size_t nr; struct page** pages; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 scalar_t__ pagevec_count (struct pagevec*) ; 

__attribute__((used)) static void *pool_alloc(struct pagevec *pv, gfp_t gfp)
{
	struct page *p;

	p = alloc_page(gfp);
	if (!p && pagevec_count(pv))
		p = pv->pages[--pv->nr];

	return p ? page_address(p) : NULL;
}