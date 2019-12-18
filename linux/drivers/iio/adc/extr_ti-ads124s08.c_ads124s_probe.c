#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct spi_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_2__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct ads124s_private {int /*<<< orphan*/  lock; TYPE_8__* chip_info; struct spi_device* spi; int /*<<< orphan*/  reset_gpio; } ;
struct TYPE_11__ {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 TYPE_8__* ads124s_chip_info_tbl ; 
 int /*<<< orphan*/  ads124s_info ; 
 int /*<<< orphan*/  ads124s_reset (struct iio_dev*) ; 
 int /*<<< orphan*/  ads124s_trigger_handler ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 int devm_iio_triggered_buffer_setup (TYPE_2__*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ads124s_private* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ads124s_probe(struct spi_device *spi)
{
	struct ads124s_private *ads124s_priv;
	struct iio_dev *indio_dev;
	const struct spi_device_id *spi_id = spi_get_device_id(spi);
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*ads124s_priv));
	if (indio_dev == NULL)
		return -ENOMEM;

	ads124s_priv = iio_priv(indio_dev);

	ads124s_priv->reset_gpio = devm_gpiod_get_optional(&spi->dev,
						   "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ads124s_priv->reset_gpio))
		dev_info(&spi->dev, "Reset GPIO not defined\n");

	ads124s_priv->chip_info = &ads124s_chip_info_tbl[spi_id->driver_data];

	spi_set_drvdata(spi, indio_dev);

	ads124s_priv->spi = spi;

	indio_dev->name = spi_id->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->dev.of_node = spi->dev.of_node;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ads124s_priv->chip_info->channels;
	indio_dev->num_channels = ads124s_priv->chip_info->num_channels;
	indio_dev->info = &ads124s_info;

	mutex_init(&ads124s_priv->lock);

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev, NULL,
					      ads124s_trigger_handler, NULL);
	if (ret) {
		dev_err(&spi->dev, "iio triggered buffer setup failed\n");
		return ret;
	}

	ads124s_reset(indio_dev);

	return devm_iio_device_register(&spi->dev, indio_dev);
}