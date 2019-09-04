#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct iio_buffer {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; struct iio_dev* driver_data; } ;
struct acpi_als {int /*<<< orphan*/  lock; struct acpi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALS_DEVICE_NAME ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_BUFFER_SOFTWARE ; 
 int /*<<< orphan*/  acpi_als_channels ; 
 int /*<<< orphan*/  acpi_als_info ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct iio_buffer* devm_iio_kfifo_allocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_attach_buffer (struct iio_dev*,struct iio_buffer*) ; 
 struct acpi_als* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_als_add(struct acpi_device *device)
{
	struct acpi_als *als;
	struct iio_dev *indio_dev;
	struct iio_buffer *buffer;

	indio_dev = devm_iio_device_alloc(&device->dev, sizeof(*als));
	if (!indio_dev)
		return -ENOMEM;

	als = iio_priv(indio_dev);

	device->driver_data = indio_dev;
	als->device = device;
	mutex_init(&als->lock);

	indio_dev->name = ACPI_ALS_DEVICE_NAME;
	indio_dev->dev.parent = &device->dev;
	indio_dev->info = &acpi_als_info;
	indio_dev->modes = INDIO_BUFFER_SOFTWARE;
	indio_dev->channels = acpi_als_channels;
	indio_dev->num_channels = ARRAY_SIZE(acpi_als_channels);

	buffer = devm_iio_kfifo_allocate(&device->dev);
	if (!buffer)
		return -ENOMEM;

	iio_device_attach_buffer(indio_dev, buffer);

	return devm_iio_device_register(&device->dev, indio_dev);
}