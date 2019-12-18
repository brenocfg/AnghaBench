#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t nr; struct page** pages; } ;
struct pagestash {int /*<<< orphan*/  lock; TYPE_1__ pvec; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *stash_pop_page(struct pagestash *stash)
{
	struct page *page = NULL;

	spin_lock(&stash->lock);
	if (likely(stash->pvec.nr))
		page = stash->pvec.pages[--stash->pvec.nr];
	spin_unlock(&stash->lock);

	return page;
}