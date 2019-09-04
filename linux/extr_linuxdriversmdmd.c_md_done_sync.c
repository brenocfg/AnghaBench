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
struct mddev {int /*<<< orphan*/  thread; int /*<<< orphan*/  recovery; int /*<<< orphan*/  recovery_wait; int /*<<< orphan*/  recovery_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_RECOVERY_ERROR ; 
 int /*<<< orphan*/  MD_RECOVERY_INTR ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void md_done_sync(struct mddev *mddev, int blocks, int ok)
{
	/* another "blocks" (512byte) blocks have been synced */
	atomic_sub(blocks, &mddev->recovery_active);
	wake_up(&mddev->recovery_wait);
	if (!ok) {
		set_bit(MD_RECOVERY_INTR, &mddev->recovery);
		set_bit(MD_RECOVERY_ERROR, &mddev->recovery);
		md_wakeup_thread(mddev->thread);
		// stop recovery, signal do_sync ....
	}
}