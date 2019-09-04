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
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct page* page_chain_next (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *page_chain_del(struct page **head, int n)
{
	struct page *page;
	struct page *tmp;

	BUG_ON(!n);
	BUG_ON(!head);

	page = *head;

	if (!page)
		return NULL;

	while (page) {
		tmp = page_chain_next(page);
		if (--n == 0)
			break; /* found sufficient pages */
		if (tmp == NULL)
			/* insufficient pages, don't use any of them. */
			return NULL;
		page = tmp;
	}

	/* add end of list marker for the returned list */
	set_page_private(page, 0);
	/* actual return value, and adjustment of head */
	page = *head;
	*head = tmp;
	return page;
}