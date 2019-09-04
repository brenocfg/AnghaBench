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
struct loop_device {int lo_flags; scalar_t__ lo_state; int /*<<< orphan*/  lo_queue; int /*<<< orphan*/  lo_refcnt; } ;
struct gendisk {struct loop_device* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int LO_FLAGS_AUTOCLEAR ; 
 scalar_t__ Lo_bound ; 
 scalar_t__ Lo_rundown ; 
 int /*<<< orphan*/  __loop_clr_fd (struct loop_device*,int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_ctl_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lo_release(struct gendisk *disk, fmode_t mode)
{
	struct loop_device *lo;

	mutex_lock(&loop_ctl_mutex);
	lo = disk->private_data;
	if (atomic_dec_return(&lo->lo_refcnt))
		goto out_unlock;

	if (lo->lo_flags & LO_FLAGS_AUTOCLEAR) {
		if (lo->lo_state != Lo_bound)
			goto out_unlock;
		lo->lo_state = Lo_rundown;
		mutex_unlock(&loop_ctl_mutex);
		/*
		 * In autoclear mode, stop the loop thread
		 * and remove configuration after last close.
		 */
		__loop_clr_fd(lo, true);
		return;
	} else if (lo->lo_state == Lo_bound) {
		/*
		 * Otherwise keep thread (if running) and config,
		 * but flush possible ongoing bios in thread.
		 */
		blk_mq_freeze_queue(lo->lo_queue);
		blk_mq_unfreeze_queue(lo->lo_queue);
	}

out_unlock:
	mutex_unlock(&loop_ctl_mutex);
}