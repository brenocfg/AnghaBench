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
struct page_list {struct page_list* next; int /*<<< orphan*/  page; } ;
struct dm_integrity_c {int journal_pages; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  alloc_page (int) ; 
 int /*<<< orphan*/  dm_integrity_free_page_list (struct dm_integrity_c*,struct page_list*) ; 
 struct page_list* kvmalloc (size_t,int) ; 

__attribute__((used)) static struct page_list *dm_integrity_alloc_page_list(struct dm_integrity_c *ic)
{
	size_t page_list_desc_size = ic->journal_pages * sizeof(struct page_list);
	struct page_list *pl;
	unsigned i;

	pl = kvmalloc(page_list_desc_size, GFP_KERNEL | __GFP_ZERO);
	if (!pl)
		return NULL;

	for (i = 0; i < ic->journal_pages; i++) {
		pl[i].page = alloc_page(GFP_KERNEL);
		if (!pl[i].page) {
			dm_integrity_free_page_list(ic, pl);
			return NULL;
		}
		if (i)
			pl[i - 1].next = &pl[i];
	}

	return pl;
}