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
struct dm_kcopyd_client {scalar_t__ nr_free_pages; scalar_t__ nr_reserved_pages; struct page_list* pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pl (struct page_list*) ; 

__attribute__((used)) static void kcopyd_put_pages(struct dm_kcopyd_client *kc, struct page_list *pl)
{
	struct page_list *next;

	do {
		next = pl->next;

		if (kc->nr_free_pages >= kc->nr_reserved_pages)
			free_pl(pl);
		else {
			pl->next = kc->pages;
			kc->pages = pl;
			kc->nr_free_pages++;
		}

		pl = next;
	} while (pl);
}