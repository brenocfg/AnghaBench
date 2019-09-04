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
struct iio_dev {int /*<<< orphan*/  buffer; int /*<<< orphan*/  modes; int /*<<< orphan*/  pollfunc; int /*<<< orphan*/  id; int /*<<< orphan*/ * setup_ops; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_BUFFER_TRIGGERED ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  iio_alloc_pollfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iio_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_attach_buffer (struct iio_dev*,struct iio_buffer*) ; 
 struct iio_buffer* iio_kfifo_allocate () ; 
 int /*<<< orphan*/  iio_kfifo_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_simple_dummy_buffer_setup_ops ; 
 int /*<<< orphan*/  iio_simple_dummy_trigger_h ; 

int iio_simple_dummy_configure_buffer(struct iio_dev *indio_dev)
{
	int ret;
	struct iio_buffer *buffer;

	/* Allocate a buffer to use - here a kfifo */
	buffer = iio_kfifo_allocate();
	if (!buffer) {
		ret = -ENOMEM;
		goto error_ret;
	}

	iio_device_attach_buffer(indio_dev, buffer);

	/*
	 * Tell the core what device type specific functions should
	 * be run on either side of buffer capture enable / disable.
	 */
	indio_dev->setup_ops = &iio_simple_dummy_buffer_setup_ops;

	/*
	 * Configure a polling function.
	 * When a trigger event with this polling function connected
	 * occurs, this function is run. Typically this grabs data
	 * from the device.
	 *
	 * NULL for the bottom half. This is normally implemented only if we
	 * either want to ping a capture now pin (no sleeping) or grab
	 * a timestamp as close as possible to a data ready trigger firing.
	 *
	 * IRQF_ONESHOT ensures irqs are masked such that only one instance
	 * of the handler can run at a time.
	 *
	 * "iio_simple_dummy_consumer%d" formatting string for the irq 'name'
	 * as seen under /proc/interrupts. Remaining parameters as per printk.
	 */
	indio_dev->pollfunc = iio_alloc_pollfunc(NULL,
						 &iio_simple_dummy_trigger_h,
						 IRQF_ONESHOT,
						 indio_dev,
						 "iio_simple_dummy_consumer%d",
						 indio_dev->id);

	if (!indio_dev->pollfunc) {
		ret = -ENOMEM;
		goto error_free_buffer;
	}

	/*
	 * Notify the core that this device is capable of buffered capture
	 * driven by a trigger.
	 */
	indio_dev->modes |= INDIO_BUFFER_TRIGGERED;

	return 0;

error_free_buffer:
	iio_kfifo_free(indio_dev->buffer);
error_ret:
	return ret;
}