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

/* Variables and functions */
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 

__attribute__((used)) static int genwqe_free_user_pages(struct page **page_list,
			unsigned int nr_pages, int dirty)
{
	unsigned int i;

	for (i = 0; i < nr_pages; i++) {
		if (page_list[i] != NULL) {
			if (dirty)
				set_page_dirty_lock(page_list[i]);
			put_page(page_list[i]);
		}
	}
	return 0;
}