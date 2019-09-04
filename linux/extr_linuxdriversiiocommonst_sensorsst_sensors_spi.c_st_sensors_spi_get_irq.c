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
struct st_sensor_data {int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {unsigned int irq; } ;

/* Variables and functions */
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 TYPE_1__* to_spi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int st_sensors_spi_get_irq(struct iio_dev *indio_dev)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);

	return to_spi_device(sdata->dev)->irq;
}