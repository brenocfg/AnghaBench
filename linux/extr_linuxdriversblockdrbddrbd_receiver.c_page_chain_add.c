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
 struct page* page_chain_tail (struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 

__attribute__((used)) static void page_chain_add(struct page **head,
		struct page *chain_first, struct page *chain_last)
{
#if 1
	struct page *tmp;
	tmp = page_chain_tail(chain_first, NULL);
	BUG_ON(tmp != chain_last);
#endif

	/* add chain to head */
	set_page_private(chain_last, (unsigned long)*head);
	*head = chain_first;
}