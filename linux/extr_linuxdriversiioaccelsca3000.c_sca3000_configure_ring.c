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
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  dev; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_BUFFER_SOFTWARE ; 
 struct iio_buffer* devm_iio_kfifo_allocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_attach_buffer (struct iio_dev*,struct iio_buffer*) ; 

__attribute__((used)) static int sca3000_configure_ring(struct iio_dev *indio_dev)
{
	struct iio_buffer *buffer;

	buffer = devm_iio_kfifo_allocate(&indio_dev->dev);
	if (!buffer)
		return -ENOMEM;

	iio_device_attach_buffer(indio_dev, buffer);
	indio_dev->modes |= INDIO_BUFFER_SOFTWARE;

	return 0;
}