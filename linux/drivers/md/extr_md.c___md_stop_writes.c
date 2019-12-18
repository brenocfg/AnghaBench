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
struct mddev {scalar_t__ ro; int in_sync; int /*<<< orphan*/ * wb_info_pool; scalar_t__ sb_flags; TYPE_1__* pers; int /*<<< orphan*/  safemode_timer; int /*<<< orphan*/  recovery; scalar_t__ sync_thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* quiesce ) (struct mddev*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_FROZEN ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_bitmap_flush (struct mddev*) ; 
 int /*<<< orphan*/  md_misc_wq ; 
 int /*<<< orphan*/  md_reap_sync_thread (struct mddev*) ; 
 int /*<<< orphan*/  md_update_sb (struct mddev*,int) ; 
 int /*<<< orphan*/  mddev_is_clustered (struct mddev*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub2 (struct mddev*,int) ; 

__attribute__((used)) static void __md_stop_writes(struct mddev *mddev)
{
	set_bit(MD_RECOVERY_FROZEN, &mddev->recovery);
	flush_workqueue(md_misc_wq);
	if (mddev->sync_thread) {
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		md_reap_sync_thread(mddev);
	}

	del_timer_sync(&mddev->safemode_timer);

	if (mddev->pers && mddev->pers->quiesce) {
		mddev->pers->quiesce(mddev, 1);
		mddev->pers->quiesce(mddev, 0);
	}
	md_bitmap_flush(mddev);

	if (mddev->ro == 0 &&
	    ((!mddev->in_sync && !mddev_is_clustered(mddev)) ||
	     mddev->sb_flags)) {
		/* mark array as shutdown cleanly */
		if (!mddev_is_clustered(mddev))
			mddev->in_sync = 1;
		md_update_sb(mddev, 1);
	}
	mempool_destroy(mddev->wb_info_pool);
	mddev->wb_info_pool = NULL;
}