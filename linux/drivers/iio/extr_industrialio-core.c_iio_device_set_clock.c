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
struct iio_event_interface {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  mlock; int /*<<< orphan*/  clock_id; struct iio_event_interface* event_interface; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 scalar_t__ iio_event_enabled (struct iio_event_interface const*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iio_device_set_clock(struct iio_dev *indio_dev, clockid_t clock_id)
{
	int ret;
	const struct iio_event_interface *ev_int = indio_dev->event_interface;

	ret = mutex_lock_interruptible(&indio_dev->mlock);
	if (ret)
		return ret;
	if ((ev_int && iio_event_enabled(ev_int)) ||
	    iio_buffer_enabled(indio_dev)) {
		mutex_unlock(&indio_dev->mlock);
		return -EBUSY;
	}
	indio_dev->clock_id = clock_id;
	mutex_unlock(&indio_dev->mlock);

	return 0;
}