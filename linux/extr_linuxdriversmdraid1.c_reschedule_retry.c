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
struct r1conf {int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  device_lock; int /*<<< orphan*/ * nr_queued; int /*<<< orphan*/  retry_list; } ;
struct r1bio {int /*<<< orphan*/  retry_list; int /*<<< orphan*/  sector; struct mddev* mddev; } ;
struct mddev {int /*<<< orphan*/  thread; struct r1conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int sector_to_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reschedule_retry(struct r1bio *r1_bio)
{
	unsigned long flags;
	struct mddev *mddev = r1_bio->mddev;
	struct r1conf *conf = mddev->private;
	int idx;

	idx = sector_to_idx(r1_bio->sector);
	spin_lock_irqsave(&conf->device_lock, flags);
	list_add(&r1_bio->retry_list, &conf->retry_list);
	atomic_inc(&conf->nr_queued[idx]);
	spin_unlock_irqrestore(&conf->device_lock, flags);

	wake_up(&conf->wait_barrier);
	md_wakeup_thread(mddev->thread);
}