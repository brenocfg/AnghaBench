#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spi_device_id {size_t driver_data; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct spi_device {TYPE_3__ dev; } ;
struct TYPE_5__ {TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_2__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; } ;
struct adis16080_state {int /*<<< orphan*/ * info; struct spi_device* us; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  adis16080_channels ; 
 int /*<<< orphan*/ * adis16080_chip_info ; 
 int /*<<< orphan*/  adis16080_info ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct adis16080_state* iio_priv (struct iio_dev*) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int adis16080_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	struct adis16080_state *st;
	struct iio_dev *indio_dev;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;
	st = iio_priv(indio_dev);
	/* this is only used for removal purposes */
	spi_set_drvdata(spi, indio_dev);

	/* Allocate the comms buffers */
	st->us = spi;
	st->info = &adis16080_chip_info[id->driver_data];

	indio_dev->name = spi->dev.driver->name;
	indio_dev->channels = adis16080_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16080_channels);
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &adis16080_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	return iio_device_register(indio_dev);
}