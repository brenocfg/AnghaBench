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
struct page_list {struct page_list* next; } ;
struct dm_kcopyd_client {unsigned int nr_reserved_pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct page_list* alloc_pl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_pages (struct page_list*) ; 
 int /*<<< orphan*/  kcopyd_put_pages (struct dm_kcopyd_client*,struct page_list*) ; 

__attribute__((used)) static int client_reserve_pages(struct dm_kcopyd_client *kc, unsigned nr_pages)
{
	unsigned i;
	struct page_list *pl = NULL, *next;

	for (i = 0; i < nr_pages; i++) {
		next = alloc_pl(GFP_KERNEL);
		if (!next) {
			if (pl)
				drop_pages(pl);
			return -ENOMEM;
		}
		next->next = pl;
		pl = next;
	}

	kc->nr_reserved_pages += nr_pages;
	kcopyd_put_pages(kc, pl);

	return 0;
}