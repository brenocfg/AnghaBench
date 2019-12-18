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
struct spi_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct max5481_data {int /*<<< orphan*/ * cfg; struct spi_device* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  MAX5481_COPY_NV_TO_AB ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct max5481_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/ * max5481_cfg ; 
 int /*<<< orphan*/  max5481_channels ; 
 int /*<<< orphan*/  max5481_info ; 
 int max5481_write_cmd (struct max5481_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 

__attribute__((used)) static int max5481_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct max5481_data *data;
	const struct spi_device_id *id = spi_get_device_id(spi);
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	dev_set_drvdata(&spi->dev, indio_dev);
	data = iio_priv(indio_dev);

	data->spi = spi;

	data->cfg = of_device_get_match_data(&spi->dev);
	if (!data->cfg)
		data->cfg = &max5481_cfg[id->driver_data];

	indio_dev->name = id->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;

	/* variant specific configuration */
	indio_dev->info = &max5481_info;
	indio_dev->channels = max5481_channels;
	indio_dev->num_channels = ARRAY_SIZE(max5481_channels);

	/* restore wiper from NV */
	ret = max5481_write_cmd(data, MAX5481_COPY_NV_TO_AB, 0);
	if (ret < 0)
		return ret;

	return iio_device_register(indio_dev);
}