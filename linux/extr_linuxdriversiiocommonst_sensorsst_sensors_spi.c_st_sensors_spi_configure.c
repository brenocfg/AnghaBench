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
struct st_sensor_data {int /*<<< orphan*/  get_irq_data_ready; int /*<<< orphan*/ * tf; int /*<<< orphan*/ * dev; } ;
struct spi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  modalias; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  st_sensors_spi_get_irq ; 
 int /*<<< orphan*/  st_sensors_tf_spi ; 

void st_sensors_spi_configure(struct iio_dev *indio_dev,
			struct spi_device *spi, struct st_sensor_data *sdata)
{
	spi_set_drvdata(spi, indio_dev);

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi->modalias;

	sdata->dev = &spi->dev;
	sdata->tf = &st_sensors_tf_spi;
	sdata->get_irq_data_ready = st_sensors_spi_get_irq;
}