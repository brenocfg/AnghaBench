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
struct page {int dummy; } ;
struct TYPE_2__ {int target_unpopulated; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 scalar_t__ XEN_PAGE_SIZE ; 
 int add_ballooned_pages (int) ; 
 int /*<<< orphan*/  balloon_mutex ; 
 struct page* balloon_retrieve (int) ; 
 TYPE_1__ balloon_stats ; 
 int /*<<< orphan*/  free_xenballooned_pages (int,struct page**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int xen_alloc_p2m_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_feature (int /*<<< orphan*/ ) ; 

int alloc_xenballooned_pages(int nr_pages, struct page **pages)
{
	int pgno = 0;
	struct page *page;
	int ret;

	mutex_lock(&balloon_mutex);

	balloon_stats.target_unpopulated += nr_pages;

	while (pgno < nr_pages) {
		page = balloon_retrieve(true);
		if (page) {
			pages[pgno++] = page;
#ifdef CONFIG_XEN_HAVE_PVMMU
			/*
			 * We don't support PV MMU when Linux and Xen is using
			 * different page granularity.
			 */
			BUILD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

			if (!xen_feature(XENFEAT_auto_translated_physmap)) {
				ret = xen_alloc_p2m_entry(page_to_pfn(page));
				if (ret < 0)
					goto out_undo;
			}
#endif
		} else {
			ret = add_ballooned_pages(nr_pages - pgno);
			if (ret < 0)
				goto out_undo;
		}
	}
	mutex_unlock(&balloon_mutex);
	return 0;
 out_undo:
	mutex_unlock(&balloon_mutex);
	free_xenballooned_pages(pgno, pages);
	return ret;
}