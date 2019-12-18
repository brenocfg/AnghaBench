#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r5l_log {TYPE_2__* reclaim_thread; TYPE_1__* rdev; } ;
struct mddev {int /*<<< orphan*/  sb_wait; } ;
struct TYPE_4__ {int /*<<< orphan*/  tsk; } ;
struct TYPE_3__ {struct mddev* mddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MaxSector ; 
 int /*<<< orphan*/  kthread_park (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_unpark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r5l_do_reclaim (struct r5l_log*) ; 
 int /*<<< orphan*/  r5l_wake_reclaim (struct r5l_log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void r5l_quiesce(struct r5l_log *log, int quiesce)
{
	struct mddev *mddev;

	if (quiesce) {
		/* make sure r5l_write_super_and_discard_space exits */
		mddev = log->rdev->mddev;
		wake_up(&mddev->sb_wait);
		kthread_park(log->reclaim_thread->tsk);
		r5l_wake_reclaim(log, MaxSector);
		r5l_do_reclaim(log);
	} else
		kthread_unpark(log->reclaim_thread->tsk);
}