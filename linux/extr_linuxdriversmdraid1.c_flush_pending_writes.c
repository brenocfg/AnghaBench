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
struct TYPE_2__ {scalar_t__ head; } ;
struct r1conf {int /*<<< orphan*/  device_lock; scalar_t__ pending_count; TYPE_1__ pending_bio_list; } ;
struct blk_plug {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 struct bio* bio_list_get (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  flush_bio_list (struct r1conf*,struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_pending_writes(struct r1conf *conf)
{
	/* Any writes that have been queued but are awaiting
	 * bitmap updates get flushed here.
	 */
	spin_lock_irq(&conf->device_lock);

	if (conf->pending_bio_list.head) {
		struct blk_plug plug;
		struct bio *bio;

		bio = bio_list_get(&conf->pending_bio_list);
		conf->pending_count = 0;
		spin_unlock_irq(&conf->device_lock);

		/*
		 * As this is called in a wait_event() loop (see freeze_array),
		 * current->state might be TASK_UNINTERRUPTIBLE which will
		 * cause a warning when we prepare to wait again.  As it is
		 * rare that this path is taken, it is perfectly safe to force
		 * us to go around the wait_event() loop again, so the warning
		 * is a false-positive.  Silence the warning by resetting
		 * thread state
		 */
		__set_current_state(TASK_RUNNING);
		blk_start_plug(&plug);
		flush_bio_list(conf, bio);
		blk_finish_plug(&plug);
	} else
		spin_unlock_irq(&conf->device_lock);
}