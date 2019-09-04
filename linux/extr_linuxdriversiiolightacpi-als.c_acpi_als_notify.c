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
typedef  int u32 ;
struct iio_dev {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;
struct acpi_als {int /*<<< orphan*/  lock; int /*<<< orphan*/ * evt_buffer; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALS_EVT_BUFFER_SIZE ; 
 int /*<<< orphan*/  ACPI_ALS_ILLUMINANCE ; 
#define  ACPI_ALS_NOTIFY_ILLUMINANCE 128 
 int acpi_als_read_value (struct acpi_als*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct iio_dev* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct acpi_als* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_als_notify(struct acpi_device *device, u32 event)
{
	struct iio_dev *indio_dev = acpi_driver_data(device);
	struct acpi_als *als = iio_priv(indio_dev);
	s32 *buffer = als->evt_buffer;
	s64 time_ns = iio_get_time_ns(indio_dev);
	s32 val;
	int ret;

	mutex_lock(&als->lock);

	memset(buffer, 0, ACPI_ALS_EVT_BUFFER_SIZE);

	switch (event) {
	case ACPI_ALS_NOTIFY_ILLUMINANCE:
		ret = acpi_als_read_value(als, ACPI_ALS_ILLUMINANCE, &val);
		if (ret < 0)
			goto out;
		*buffer++ = val;
		break;
	default:
		/* Unhandled event */
		dev_dbg(&device->dev, "Unhandled ACPI ALS event (%08x)!\n",
			event);
		goto out;
	}

	iio_push_to_buffers_with_timestamp(indio_dev, als->evt_buffer, time_ns);

out:
	mutex_unlock(&als->lock);
}