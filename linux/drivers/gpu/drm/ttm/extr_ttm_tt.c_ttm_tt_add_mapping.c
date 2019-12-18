#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_tt {int page_flags; size_t num_pages; TYPE_2__* bdev; TYPE_1__** pages; } ;
typedef  size_t pgoff_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  mapping; } ;

/* Variables and functions */
 int TTM_PAGE_FLAG_SG ; 

__attribute__((used)) static void ttm_tt_add_mapping(struct ttm_tt *ttm)
{
	pgoff_t i;

	if (ttm->page_flags & TTM_PAGE_FLAG_SG)
		return;

	for (i = 0; i < ttm->num_pages; ++i)
		ttm->pages[i]->mapping = ttm->bdev->dev_mapping;
}