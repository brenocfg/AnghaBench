#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* driver; } ;
struct spi_device {TYPE_4__ dev; } ;
struct TYPE_6__ {TYPE_4__* parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct adxrs450_state {int /*<<< orphan*/  buf_lock; struct spi_device* us; } ;
struct TYPE_8__ {size_t driver_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/ * adxrs450_channels ; 
 int /*<<< orphan*/  adxrs450_info ; 
 int adxrs450_initial_setup (struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_4__*,int) ; 
 int devm_iio_device_register (TYPE_4__*,struct iio_dev*) ; 
 struct adxrs450_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int adxrs450_probe(struct spi_device *spi)
{
	int ret;
	struct adxrs450_state *st;
	struct iio_dev *indio_dev;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;
	st = iio_priv(indio_dev);
	st->us = spi;
	mutex_init(&st->buf_lock);
	/* This is only used for removal purposes */
	spi_set_drvdata(spi, indio_dev);

	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &adxrs450_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels =
		adxrs450_channels[spi_get_device_id(spi)->driver_data];
	indio_dev->num_channels = ARRAY_SIZE(adxrs450_channels);
	indio_dev->name = spi->dev.driver->name;

	ret = devm_iio_device_register(&spi->dev, indio_dev);
	if (ret)
		return ret;

	/* Get the device into a sane initial state */
	ret = adxrs450_initial_setup(indio_dev);
	if (ret)
		return ret;

	return 0;
}