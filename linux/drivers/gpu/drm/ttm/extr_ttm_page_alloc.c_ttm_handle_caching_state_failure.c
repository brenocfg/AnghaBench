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
struct page {int /*<<< orphan*/  lru; } ;
struct list_head {int dummy; } ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ttm_handle_caching_state_failure(struct list_head *pages,
		int ttm_flags, enum ttm_caching_state cstate,
		struct page **failed_pages, unsigned cpages)
{
	unsigned i;
	/* Failed pages have to be freed */
	for (i = 0; i < cpages; ++i) {
		list_del(&failed_pages[i]->lru);
		__free_page(failed_pages[i]);
	}
}