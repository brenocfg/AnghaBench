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
struct iio_dev {int /*<<< orphan*/  info_exist_lock; int /*<<< orphan*/ * info; int /*<<< orphan*/  dev; int /*<<< orphan*/  chrdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_buffer_free_sysfs_and_mask (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_buffer_wakeup_poll (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_debugfs (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_wakeup_eventset (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_disable_all_buffers (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void iio_device_unregister(struct iio_dev *indio_dev)
{
	cdev_device_del(&indio_dev->chrdev, &indio_dev->dev);

	mutex_lock(&indio_dev->info_exist_lock);

	iio_device_unregister_debugfs(indio_dev);

	iio_disable_all_buffers(indio_dev);

	indio_dev->info = NULL;

	iio_device_wakeup_eventset(indio_dev);
	iio_buffer_wakeup_poll(indio_dev);

	mutex_unlock(&indio_dev->info_exist_lock);

	iio_buffer_free_sysfs_and_mask(indio_dev);
}