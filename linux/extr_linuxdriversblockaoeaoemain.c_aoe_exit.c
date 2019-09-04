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

/* Variables and functions */
 int /*<<< orphan*/  AOE_MAJOR ; 
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  aoeblk_exit () ; 
 int /*<<< orphan*/  aoechr_exit () ; 
 int /*<<< orphan*/  aoecmd_exit () ; 
 int /*<<< orphan*/  aoedev_exit () ; 
 int /*<<< orphan*/  aoenet_exit () ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aoe_exit(void)
{
	del_timer_sync(&timer);

	aoenet_exit();
	unregister_blkdev(AOE_MAJOR, DEVICE_NAME);
	aoecmd_exit();
	aoechr_exit();
	aoedev_exit();
	aoeblk_exit();		/* free cache after de-allocating bufs */
}