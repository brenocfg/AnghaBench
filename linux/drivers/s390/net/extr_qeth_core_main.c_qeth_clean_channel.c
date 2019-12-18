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
struct qeth_channel {struct ccw_device* ccwdev; } ;
struct ccw_device {int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_clean_channel(struct qeth_channel *channel)
{
	struct ccw_device *cdev = channel->ccwdev;

	QETH_DBF_TEXT(SETUP, 2, "freech");

	spin_lock_irq(get_ccwdev_lock(cdev));
	cdev->handler = NULL;
	spin_unlock_irq(get_ccwdev_lock(cdev));
}