#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct adis16260 {int /*<<< orphan*/  adis; TYPE_2__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 TYPE_2__* adis16260_chip_info_table ; 
 int /*<<< orphan*/  adis16260_data ; 
 int /*<<< orphan*/  adis16260_info ; 
 int /*<<< orphan*/  adis_cleanup_buffer_and_trigger (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int adis_init (int /*<<< orphan*/ *,struct iio_dev*,struct spi_device*,int /*<<< orphan*/ *) ; 
 int adis_initial_startup (int /*<<< orphan*/ *) ; 
 int adis_setup_buffer_and_trigger (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct adis16260* iio_priv (struct iio_dev*) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int adis16260_probe(struct spi_device *spi)
{
	const struct spi_device_id *id;
	struct adis16260 *adis16260;
	struct iio_dev *indio_dev;
	int ret;

	id = spi_get_device_id(spi);
	if (!id)
		return -ENODEV;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*adis16260));
	if (!indio_dev)
		return -ENOMEM;
	adis16260 = iio_priv(indio_dev);
	/* this is only used for removal purposes */
	spi_set_drvdata(spi, indio_dev);

	adis16260->info = &adis16260_chip_info_table[id->driver_data];

	indio_dev->name = id->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &adis16260_info;
	indio_dev->channels = adis16260->info->channels;
	indio_dev->num_channels = adis16260->info->num_channels;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = adis_init(&adis16260->adis, indio_dev, spi, &adis16260_data);
	if (ret)
		return ret;

	ret = adis_setup_buffer_and_trigger(&adis16260->adis, indio_dev, NULL);
	if (ret)
		return ret;

	/* Get the device into a sane initial state */
	ret = adis_initial_startup(&adis16260->adis);
	if (ret)
		goto error_cleanup_buffer_trigger;
	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_cleanup_buffer_trigger;

	return 0;

error_cleanup_buffer_trigger:
	adis_cleanup_buffer_and_trigger(&adis16260->adis, indio_dev);
	return ret;
}