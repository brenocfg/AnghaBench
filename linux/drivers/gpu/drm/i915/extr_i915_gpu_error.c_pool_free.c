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
struct pagevec {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 scalar_t__ pagevec_space (struct pagevec*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static void pool_free(struct pagevec *pv, void *addr)
{
	struct page *p = virt_to_page(addr);

	if (pagevec_space(pv))
		pagevec_add(pv, p);
	else
		__free_page(p);
}