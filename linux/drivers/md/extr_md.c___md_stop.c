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
struct mddev {int /*<<< orphan*/  recovery; int /*<<< orphan*/ * to_remove; int /*<<< orphan*/ * private; int /*<<< orphan*/  lock; struct md_personality* pers; } ;
struct md_personality {int /*<<< orphan*/  owner; scalar_t__ sync_request; int /*<<< orphan*/  (* free ) (struct mddev*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_bitmap_destroy (struct mddev*) ; 
 int /*<<< orphan*/  md_misc_wq ; 
 int /*<<< orphan*/  md_redundancy_group ; 
 int /*<<< orphan*/  mddev_detach (struct mddev*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __md_stop(struct mddev *mddev)
{
	struct md_personality *pers = mddev->pers;
	md_bitmap_destroy(mddev);
	mddev_detach(mddev);
	/* Ensure ->event_work is done */
	flush_workqueue(md_misc_wq);
	spin_lock(&mddev->lock);
	mddev->pers = NULL;
	spin_unlock(&mddev->lock);
	pers->free(mddev, mddev->private);
	mddev->private = NULL;
	if (pers->sync_request && mddev->to_remove == NULL)
		mddev->to_remove = &md_redundancy_group;
	module_put(pers->owner);
	clear_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
}