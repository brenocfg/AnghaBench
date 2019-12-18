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
struct inode {int dummy; } ;
struct iio_event_interface {int /*<<< orphan*/  flags; } ;
struct iio_dev {struct iio_event_interface* event_interface; } ;
struct file {struct iio_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_BUSY_BIT_POS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_put (struct iio_dev*) ; 

__attribute__((used)) static int iio_event_chrdev_release(struct inode *inode, struct file *filep)
{
	struct iio_dev *indio_dev = filep->private_data;
	struct iio_event_interface *ev_int = indio_dev->event_interface;

	clear_bit(IIO_BUSY_BIT_POS, &ev_int->flags);

	iio_device_put(indio_dev);

	return 0;
}