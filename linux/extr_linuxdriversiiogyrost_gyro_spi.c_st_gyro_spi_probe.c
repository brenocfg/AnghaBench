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
struct st_sensor_data {int dummy; } ;
struct spi_device {int /*<<< orphan*/  modalias; int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int st_gyro_common_probe (struct iio_dev*) ; 
 int /*<<< orphan*/  st_gyro_of_match ; 
 int /*<<< orphan*/  st_sensors_of_name_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_sensors_spi_configure (struct iio_dev*,struct spi_device*,struct st_sensor_data*) ; 

__attribute__((used)) static int st_gyro_spi_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct st_sensor_data *gdata;
	int err;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*gdata));
	if (!indio_dev)
		return -ENOMEM;

	gdata = iio_priv(indio_dev);

	st_sensors_of_name_probe(&spi->dev, st_gyro_of_match,
				 spi->modalias, sizeof(spi->modalias));
	st_sensors_spi_configure(indio_dev, spi, gdata);

	err = st_gyro_common_probe(indio_dev);
	if (err < 0)
		return err;

	return 0;
}