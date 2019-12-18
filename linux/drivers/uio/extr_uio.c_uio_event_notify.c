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
struct uio_info {struct uio_device* uio_dev; } ;
struct uio_device {int /*<<< orphan*/  async_queue; int /*<<< orphan*/  wait; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void uio_event_notify(struct uio_info *info)
{
	struct uio_device *idev = info->uio_dev;

	atomic_inc(&idev->event);
	wake_up_interruptible(&idev->wait);
	kill_fasync(&idev->async_queue, SIGIO, POLL_IN);
}