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
struct dm_transaction_manager {int /*<<< orphan*/  bm; int /*<<< orphan*/  prefetches; } ;

/* Variables and functions */
 int /*<<< orphan*/  prefetch_issue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dm_tm_issue_prefetches(struct dm_transaction_manager *tm)
{
	prefetch_issue(&tm->prefetches, tm->bm);
}