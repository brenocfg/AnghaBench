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
struct mddev {scalar_t__ queue; int /*<<< orphan*/  thread; TYPE_1__* pers; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* quiesce ) (struct mddev*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  blk_sync_queue (scalar_t__) ; 
 int /*<<< orphan*/  md_bitmap_wait_behind_writes (struct mddev*) ; 
 int /*<<< orphan*/  md_unregister_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub2 (struct mddev*,int) ; 

__attribute__((used)) static void mddev_detach(struct mddev *mddev)
{
	md_bitmap_wait_behind_writes(mddev);
	if (mddev->pers && mddev->pers->quiesce) {
		mddev->pers->quiesce(mddev, 1);
		mddev->pers->quiesce(mddev, 0);
	}
	md_unregister_thread(&mddev->thread);
	if (mddev->queue)
		blk_sync_queue(mddev->queue); /* the unplug fn references 'conf'*/
}