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
struct multipath_bh {int /*<<< orphan*/  retry_list; struct mddev* mddev; } ;
struct mpconf {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  retry_list; } ;
struct mddev {int /*<<< orphan*/  thread; struct mpconf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void multipath_reschedule_retry (struct multipath_bh *mp_bh)
{
	unsigned long flags;
	struct mddev *mddev = mp_bh->mddev;
	struct mpconf *conf = mddev->private;

	spin_lock_irqsave(&conf->device_lock, flags);
	list_add(&mp_bh->retry_list, &conf->retry_list);
	spin_unlock_irqrestore(&conf->device_lock, flags);
	md_wakeup_thread(mddev->thread);
}