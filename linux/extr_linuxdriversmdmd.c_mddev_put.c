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
struct mddev {scalar_t__ ctime; int /*<<< orphan*/  del_work; int /*<<< orphan*/  all_mddevs; int /*<<< orphan*/  hold_active; int /*<<< orphan*/  disks; int /*<<< orphan*/  raid_disks; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_mddevs_lock ; 
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_misc_wq ; 
 int /*<<< orphan*/  mddev_delayed_delete ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mddev_put(struct mddev *mddev)
{
	if (!atomic_dec_and_lock(&mddev->active, &all_mddevs_lock))
		return;
	if (!mddev->raid_disks && list_empty(&mddev->disks) &&
	    mddev->ctime == 0 && !mddev->hold_active) {
		/* Array is not configured at all, and not held active,
		 * so destroy it */
		list_del_init(&mddev->all_mddevs);

		/*
		 * Call queue_work inside the spinlock so that
		 * flush_workqueue() after mddev_find will succeed in waiting
		 * for the work to be done.
		 */
		INIT_WORK(&mddev->del_work, mddev_delayed_delete);
		queue_work(md_misc_wq, &mddev->del_work);
	}
	spin_unlock(&all_mddevs_lock);
}