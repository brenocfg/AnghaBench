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
struct vmballoon {struct page* page; TYPE_1__* batch_page; } ;
struct page {int dummy; } ;
struct TYPE_2__ {unsigned long status; int /*<<< orphan*/  pfn; } ;

/* Variables and functions */
 unsigned long VMW_BALLOON_SUCCESS ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_balloon_batching ; 

__attribute__((used)) static unsigned long vmballoon_status_page(struct vmballoon *b, int idx,
					   struct page **p)
{
	if (static_branch_likely(&vmw_balloon_batching)) {
		/* batching mode */
		*p = pfn_to_page(b->batch_page[idx].pfn);
		return b->batch_page[idx].status;
	}

	/* non-batching mode */
	*p = b->page;

	/*
	 * If a failure occurs, the indication will be provided in the status
	 * of the entire operation, which is considered before the individual
	 * page status. So for non-batching mode, the indication is always of
	 * success.
	 */
	return VMW_BALLOON_SUCCESS;
}