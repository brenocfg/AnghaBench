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
struct dasd_ccw_req {TYPE_1__* startdev; int /*<<< orphan*/  callback_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_SLEEPON_END_TAG ; 
 int /*<<< orphan*/  generic_waitq ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dasd_wakeup_cb(struct dasd_ccw_req *cqr, void *data)
{
	spin_lock_irq(get_ccwdev_lock(cqr->startdev->cdev));
	cqr->callback_data = DASD_SLEEPON_END_TAG;
	spin_unlock_irq(get_ccwdev_lock(cqr->startdev->cdev));
	wake_up(&generic_waitq);
}