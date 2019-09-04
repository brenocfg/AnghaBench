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
struct grant {int /*<<< orphan*/  page; int /*<<< orphan*/  gref; } ;
struct blkfront_info {TYPE_1__* xbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  otherend_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_page_grant_foreign_access_ref_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void grant_foreign_access(const struct grant *gnt_list_entry,
					const struct blkfront_info *info)
{
	gnttab_page_grant_foreign_access_ref_one(gnt_list_entry->gref,
						 info->xbdev->otherend_id,
						 gnt_list_entry->page,
						 0);
}