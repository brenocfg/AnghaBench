#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* driver; } ;
struct spi_device {TYPE_3__ dev; } ;
struct TYPE_6__ {TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_2__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; } ;
struct adis16130_state {int /*<<< orphan*/  buf_lock; struct spi_device* us; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  adis16130_channels ; 
 int /*<<< orphan*/  adis16130_info ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int devm_iio_device_register (TYPE_3__*,struct iio_dev*) ; 
 struct adis16130_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int adis16130_probe(struct spi_device *spi)
{
	struct adis16130_state *st;
	struct iio_dev *indio_dev;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;
	st = iio_priv(indio_dev);
	/* this is only used for removal purposes */
	spi_set_drvdata(spi, indio_dev);
	st->us = spi;
	mutex_init(&st->buf_lock);
	indio_dev->name = spi->dev.driver->name;
	indio_dev->channels = adis16130_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16130_channels);
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &adis16130_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	return devm_iio_device_register(&spi->dev, indio_dev);
}