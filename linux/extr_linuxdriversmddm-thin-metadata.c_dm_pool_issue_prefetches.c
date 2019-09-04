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
struct dm_pool_metadata {int /*<<< orphan*/  root_lock; int /*<<< orphan*/  tm; int /*<<< orphan*/  fail_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_tm_issue_prefetches (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void dm_pool_issue_prefetches(struct dm_pool_metadata *pmd)
{
	down_read(&pmd->root_lock);
	if (!pmd->fail_io)
		dm_tm_issue_prefetches(pmd->tm);
	up_read(&pmd->root_lock);
}