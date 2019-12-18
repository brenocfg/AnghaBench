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
struct uio_info {scalar_t__ irq; struct uio_device* uio_dev; } ;
struct uio_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  async_queue; int /*<<< orphan*/  wait; int /*<<< orphan*/  info_lock; int /*<<< orphan*/ * info; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_HUP ; 
 int /*<<< orphan*/  SIGIO ; 
 scalar_t__ UIO_IRQ_CUSTOM ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct uio_device*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_dev_del_attributes (struct uio_device*) ; 
 int /*<<< orphan*/  uio_free_minor (struct uio_device*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void uio_unregister_device(struct uio_info *info)
{
	struct uio_device *idev;

	if (!info || !info->uio_dev)
		return;

	idev = info->uio_dev;

	uio_free_minor(idev);

	mutex_lock(&idev->info_lock);
	uio_dev_del_attributes(idev);

	if (info->irq && info->irq != UIO_IRQ_CUSTOM)
		free_irq(info->irq, idev);

	idev->info = NULL;
	mutex_unlock(&idev->info_lock);

	wake_up_interruptible(&idev->wait);
	kill_fasync(&idev->async_queue, SIGIO, POLL_HUP);

	device_unregister(&idev->dev);

	return;
}