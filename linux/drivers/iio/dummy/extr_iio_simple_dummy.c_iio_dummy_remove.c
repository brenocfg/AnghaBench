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
struct iio_sw_device {struct iio_dev* device; } ;
struct iio_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_device_free (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_simple_dummy_events_unregister (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_simple_dummy_unconfigure_buffer (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iio_dummy_remove(struct iio_sw_device *swd)
{
	/*
	 * Get a pointer to the device instance iio_dev structure
	 * from the bus subsystem. E.g.
	 * struct iio_dev *indio_dev = i2c_get_clientdata(client);
	 * struct iio_dev *indio_dev = spi_get_drvdata(spi);
	 */
	struct iio_dev *indio_dev = swd->device;

	/* Unregister the device */
	iio_device_unregister(indio_dev);

	/* Device specific code to power down etc */

	/* Buffered capture related cleanup */
	iio_simple_dummy_unconfigure_buffer(indio_dev);

	iio_simple_dummy_events_unregister(indio_dev);

	/* Free all structures */
	kfree(indio_dev->name);
	iio_device_free(indio_dev);

	return 0;
}