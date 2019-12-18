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
struct page {int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int /*<<< orphan*/  balloon_low; int /*<<< orphan*/  balloon_high; } ;

/* Variables and functions */
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  __SetPageOffline (struct page*) ; 
 TYPE_1__ balloon_stats ; 
 int /*<<< orphan*/  balloon_wq ; 
 int /*<<< orphan*/  ballooned_pages ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void balloon_append(struct page *page)
{
	__SetPageOffline(page);

	/* Lowmem is re-populated first, so highmem pages go at list tail. */
	if (PageHighMem(page)) {
		list_add_tail(&page->lru, &ballooned_pages);
		balloon_stats.balloon_high++;
	} else {
		list_add(&page->lru, &ballooned_pages);
		balloon_stats.balloon_low++;
	}
	wake_up(&balloon_wq);
}