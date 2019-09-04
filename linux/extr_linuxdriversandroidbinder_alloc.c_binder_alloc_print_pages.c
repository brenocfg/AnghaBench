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
struct seq_file {int dummy; } ;
struct binder_lru_page {int /*<<< orphan*/  lru; int /*<<< orphan*/  page_ptr; } ;
struct binder_alloc {int buffer_size; int /*<<< orphan*/  pages_high; int /*<<< orphan*/  mutex; struct binder_lru_page* pages; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

void binder_alloc_print_pages(struct seq_file *m,
			      struct binder_alloc *alloc)
{
	struct binder_lru_page *page;
	int i;
	int active = 0;
	int lru = 0;
	int free = 0;

	mutex_lock(&alloc->mutex);
	for (i = 0; i < alloc->buffer_size / PAGE_SIZE; i++) {
		page = &alloc->pages[i];
		if (!page->page_ptr)
			free++;
		else if (list_empty(&page->lru))
			active++;
		else
			lru++;
	}
	mutex_unlock(&alloc->mutex);
	seq_printf(m, "  pages: %d:%d:%d\n", active, lru, free);
	seq_printf(m, "  pages high watermark: %zu\n", alloc->pages_high);
}