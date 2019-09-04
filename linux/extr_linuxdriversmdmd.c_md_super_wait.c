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
struct mddev {int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  pending_writes; int /*<<< orphan*/  sb_wait; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MD_SB_NEED_REWRITE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int md_super_wait(struct mddev *mddev)
{
	/* wait for all superblock writes that were scheduled to complete */
	wait_event(mddev->sb_wait, atomic_read(&mddev->pending_writes)==0);
	if (test_and_clear_bit(MD_SB_NEED_REWRITE, &mddev->sb_flags))
		return -EAGAIN;
	return 0;
}