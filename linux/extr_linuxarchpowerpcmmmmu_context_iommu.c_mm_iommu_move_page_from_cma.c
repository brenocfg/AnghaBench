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

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIGRATE_SYNC ; 
 int /*<<< orphan*/  MR_CONTIG_RANGE ; 
 scalar_t__ PageCompound (struct page*) ; 
 int /*<<< orphan*/  cma_migrate_pages ; 
 int isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lru_add_drain () ; 
 int migrate_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_iommu_non_cma_page ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  putback_movable_pages (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mm_iommu_move_page_from_cma(struct page *page)
{
	int ret = 0;
	LIST_HEAD(cma_migrate_pages);

	/* Ignore huge pages for now */
	if (PageCompound(page))
		return -EBUSY;

	lru_add_drain();
	ret = isolate_lru_page(page);
	if (ret)
		return ret;

	list_add(&page->lru, &cma_migrate_pages);
	put_page(page); /* Drop the gup reference */

	ret = migrate_pages(&cma_migrate_pages, new_iommu_non_cma_page,
				NULL, 0, MIGRATE_SYNC, MR_CONTIG_RANGE);
	if (ret) {
		if (!list_empty(&cma_migrate_pages))
			putback_movable_pages(&cma_migrate_pages);
	}

	return 0;
}