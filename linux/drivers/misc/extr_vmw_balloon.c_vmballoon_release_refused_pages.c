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
struct vmballoon_ctl {int /*<<< orphan*/  page_size; int /*<<< orphan*/  n_refused_pages; int /*<<< orphan*/  refused_pages; } ;
struct vmballoon {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMW_BALLOON_PAGE_STAT_REFUSED_FREE ; 
 int /*<<< orphan*/  vmballoon_release_page_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmballoon_stats_page_inc (struct vmballoon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmballoon_release_refused_pages(struct vmballoon *b,
					    struct vmballoon_ctl *ctl)
{
	vmballoon_stats_page_inc(b, VMW_BALLOON_PAGE_STAT_REFUSED_FREE,
				 ctl->page_size);

	vmballoon_release_page_list(&ctl->refused_pages, &ctl->n_refused_pages,
				    ctl->page_size);
}