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
struct page_list {scalar_t__ page; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  kvfree (struct page_list*) ; 

__attribute__((used)) static void dm_integrity_free_page_list(struct page_list *pl)
{
	unsigned i;

	if (!pl)
		return;
	for (i = 0; pl[i].page; i++)
		__free_page(pl[i].page);
	kvfree(pl);
}