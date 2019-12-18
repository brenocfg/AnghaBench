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
struct st_sensor_data {scalar_t__ irq; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  st_accel_deallocate_ring (struct iio_dev*) ; 
 int /*<<< orphan*/  st_sensors_deallocate_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  st_sensors_power_disable (struct iio_dev*) ; 

void st_accel_common_remove(struct iio_dev *indio_dev)
{
	struct st_sensor_data *adata = iio_priv(indio_dev);

	st_sensors_power_disable(indio_dev);

	iio_device_unregister(indio_dev);
	if (adata->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);

	st_accel_deallocate_ring(indio_dev);
}