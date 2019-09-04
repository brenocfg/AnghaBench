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
struct cmm_page_array {size_t index; unsigned long* pages; struct cmm_page_array* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmm_lock ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long cmm_free_pages(long nr, long *counter, struct cmm_page_array **list)
{
	struct cmm_page_array *pa;
	unsigned long addr;

	spin_lock(&cmm_lock);
	pa = *list;
	while (nr) {
		if (!pa || pa->index <= 0)
			break;
		addr = pa->pages[--pa->index];
		if (pa->index == 0) {
			pa = pa->next;
			free_page((unsigned long) *list);
			*list = pa;
		}
		free_page(addr);
		(*counter)--;
		nr--;
	}
	spin_unlock(&cmm_lock);
	return nr;
}