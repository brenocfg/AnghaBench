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
struct ltc1660_priv {int /*<<< orphan*/  vref_reg; struct spi_device* spi; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTC1660_NUM_CHANNELS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ltc1660_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/ * ltc1660_channels ; 
 int /*<<< orphan*/  ltc1660_info ; 
 int /*<<< orphan*/  ltc1660_regmap_config ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ltc1660_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct ltc1660_priv *priv;
	const struct spi_device_id *id = spi_get_device_id(spi);
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*priv));
	if (indio_dev == NULL)
		return -ENOMEM;

	priv = iio_priv(indio_dev);
	priv->regmap = devm_regmap_init_spi(spi, &ltc1660_regmap_config);
	if (IS_ERR(priv->regmap)) {
		dev_err(&spi->dev, "failed to register spi regmap %ld\n",
			PTR_ERR(priv->regmap));
		return PTR_ERR(priv->regmap);
	}

	priv->vref_reg = devm_regulator_get(&spi->dev, "vref");
	if (IS_ERR(priv->vref_reg)) {
		dev_err(&spi->dev, "vref regulator not specified\n");
		return PTR_ERR(priv->vref_reg);
	}

	ret = regulator_enable(priv->vref_reg);
	if (ret) {
		dev_err(&spi->dev, "failed to enable vref regulator: %d\n",
				ret);
		return ret;
	}

	priv->spi = spi;
	spi_set_drvdata(spi, indio_dev);
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &ltc1660_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ltc1660_channels[id->driver_data];
	indio_dev->num_channels = LTC1660_NUM_CHANNELS;
	indio_dev->name = id->name;

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&spi->dev, "failed to register iio device: %d\n",
				ret);
		goto error_disable_reg;
	}

	return 0;

error_disable_reg:
	regulator_disable(priv->vref_reg);

	return ret;
}