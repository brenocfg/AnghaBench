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
struct vmw_fence_manager {int /*<<< orphan*/  lock; int /*<<< orphan*/  cleanup_list; int /*<<< orphan*/  fence_list; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmw_fence_manager*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void vmw_fence_manager_takedown(struct vmw_fence_manager *fman)
{
	bool lists_empty;

	(void) cancel_work_sync(&fman->work);

	spin_lock(&fman->lock);
	lists_empty = list_empty(&fman->fence_list) &&
		list_empty(&fman->cleanup_list);
	spin_unlock(&fman->lock);

	BUG_ON(!lists_empty);
	kfree(fman);
}