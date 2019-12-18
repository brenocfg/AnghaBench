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
struct iio_event_interface {int /*<<< orphan*/  det_events; int /*<<< orphan*/  flags; } ;
struct iio_dev {int /*<<< orphan*/  mlock; struct iio_event_interface* event_interface; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  IIO_BUSY_BIT_POS ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct iio_dev*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_get (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_put (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_event_chrdev_fileops ; 
 int /*<<< orphan*/  kfifo_reset_out (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iio_event_getfd(struct iio_dev *indio_dev)
{
	struct iio_event_interface *ev_int = indio_dev->event_interface;
	int fd;

	if (ev_int == NULL)
		return -ENODEV;

	fd = mutex_lock_interruptible(&indio_dev->mlock);
	if (fd)
		return fd;

	if (test_and_set_bit(IIO_BUSY_BIT_POS, &ev_int->flags)) {
		fd = -EBUSY;
		goto unlock;
	}

	iio_device_get(indio_dev);

	fd = anon_inode_getfd("iio:event", &iio_event_chrdev_fileops,
				indio_dev, O_RDONLY | O_CLOEXEC);
	if (fd < 0) {
		clear_bit(IIO_BUSY_BIT_POS, &ev_int->flags);
		iio_device_put(indio_dev);
	} else {
		kfifo_reset_out(&ev_int->det_events);
	}

unlock:
	mutex_unlock(&indio_dev->mlock);
	return fd;
}