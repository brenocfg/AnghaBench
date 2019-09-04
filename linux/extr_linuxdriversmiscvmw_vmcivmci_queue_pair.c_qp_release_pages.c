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
typedef  int u64 ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static void qp_release_pages(struct page **pages,
			     u64 num_pages, bool dirty)
{
	int i;

	for (i = 0; i < num_pages; i++) {
		if (dirty)
			set_page_dirty(pages[i]);

		put_page(pages[i]);
		pages[i] = NULL;
	}
}