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
struct ion_page_pool {int order; int /*<<< orphan*/  mutex; int /*<<< orphan*/  low_count; int /*<<< orphan*/  low_items; int /*<<< orphan*/  high_count; int /*<<< orphan*/  high_items; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_KERNEL_MISC_RECLAIMABLE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 

__attribute__((used)) static void ion_page_pool_add(struct ion_page_pool *pool, struct page *page)
{
	mutex_lock(&pool->mutex);
	if (PageHighMem(page)) {
		list_add_tail(&page->lru, &pool->high_items);
		pool->high_count++;
	} else {
		list_add_tail(&page->lru, &pool->low_items);
		pool->low_count++;
	}

	mod_node_page_state(page_pgdat(page), NR_KERNEL_MISC_RECLAIMABLE,
							1 << pool->order);
	mutex_unlock(&pool->mutex);
}