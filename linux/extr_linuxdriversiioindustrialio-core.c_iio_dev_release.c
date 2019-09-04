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
struct iio_dev {int modes; int /*<<< orphan*/  id; int /*<<< orphan*/  buffer; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int INDIO_ALL_TRIGGERED_MODES ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_buffer_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister_eventset (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_sysfs (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister_trigger_consumer (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_ida ; 
 int /*<<< orphan*/  kfree (struct iio_dev*) ; 

__attribute__((used)) static void iio_dev_release(struct device *device)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(device);
	if (indio_dev->modes & INDIO_ALL_TRIGGERED_MODES)
		iio_device_unregister_trigger_consumer(indio_dev);
	iio_device_unregister_eventset(indio_dev);
	iio_device_unregister_sysfs(indio_dev);

	iio_buffer_put(indio_dev->buffer);

	ida_simple_remove(&iio_ida, indio_dev->id);
	kfree(indio_dev);
}