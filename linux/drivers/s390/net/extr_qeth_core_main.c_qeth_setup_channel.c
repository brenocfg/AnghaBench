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
struct qeth_channel {int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  state; struct ccw_device* ccwdev; } ;
struct ccw_device {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_STATE_DOWN ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  qeth_irq ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_setup_channel(struct qeth_channel *channel)
{
	struct ccw_device *cdev = channel->ccwdev;

	QETH_DBF_TEXT(SETUP, 2, "setupch");

	channel->state = CH_STATE_DOWN;
	atomic_set(&channel->irq_pending, 0);

	spin_lock_irq(get_ccwdev_lock(cdev));
	cdev->handler = qeth_irq;
	spin_unlock_irq(get_ccwdev_lock(cdev));
}