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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  name; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct dac7612 {int /*<<< orphan*/  cache; struct spi_device* spi; int /*<<< orphan*/  loaddacs; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac7612_channels ; 
 int dac7612_cmd_single (struct dac7612*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac7612_info ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct dac7612* iio_priv (struct iio_dev*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int dac7612_probe(struct spi_device *spi)
{
	struct iio_dev *iio_dev;
	struct dac7612 *priv;
	int i;
	int ret;

	iio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*priv));
	if (!iio_dev)
		return -ENOMEM;

	priv = iio_priv(iio_dev);
	/*
	 * LOADDACS pin can be controlled by the driver or externally.
	 * When controlled by the driver, the DAC value is updated after
	 * every write.
	 * When the driver does not control the PIN, the user or an external
	 * event can change the value of all DACs by pulsing down the LOADDACs
	 * pin.
	 */
	priv->loaddacs = devm_gpiod_get_optional(&spi->dev, "ti,loaddacs",
						 GPIOD_OUT_LOW);
	if (IS_ERR(priv->loaddacs))
		return PTR_ERR(priv->loaddacs);
	priv->spi = spi;
	spi_set_drvdata(spi, iio_dev);
	iio_dev->dev.parent = &spi->dev;
	iio_dev->info = &dac7612_info;
	iio_dev->modes = INDIO_DIRECT_MODE;
	iio_dev->channels = dac7612_channels;
	iio_dev->num_channels = ARRAY_SIZE(priv->cache);
	iio_dev->name = spi_get_device_id(spi)->name;

	for (i = 0; i < ARRAY_SIZE(priv->cache); i++) {
		ret = dac7612_cmd_single(priv, i, 0);
		if (ret)
			return ret;
	}

	return devm_iio_device_register(&spi->dev, iio_dev);
}