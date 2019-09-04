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
struct mei_device {int dummy; } ;
struct mei_cl {int /*<<< orphan*/  wait; int /*<<< orphan*/  ev_wait; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  rx_wait; struct mei_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mei_cl_wake_all(struct mei_cl *cl)
{
	struct mei_device *dev = cl->dev;

	/* synchronized under device mutex */
	if (waitqueue_active(&cl->rx_wait)) {
		cl_dbg(dev, cl, "Waking up reading client!\n");
		wake_up_interruptible(&cl->rx_wait);
	}
	/* synchronized under device mutex */
	if (waitqueue_active(&cl->tx_wait)) {
		cl_dbg(dev, cl, "Waking up writing client!\n");
		wake_up_interruptible(&cl->tx_wait);
	}
	/* synchronized under device mutex */
	if (waitqueue_active(&cl->ev_wait)) {
		cl_dbg(dev, cl, "Waking up waiting for event clients!\n");
		wake_up_interruptible(&cl->ev_wait);
	}
	/* synchronized under device mutex */
	if (waitqueue_active(&cl->wait)) {
		cl_dbg(dev, cl, "Waking up ctrl write clients!\n");
		wake_up(&cl->wait);
	}
}