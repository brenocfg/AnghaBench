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
struct st_sensor_data {int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; TYPE_2__* sensor_settings; } ;
struct spi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  modalias; } ;
struct regmap_config {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_4__ {scalar_t__ multi_read_bit; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_regmap_init_spi (struct spi_device*,struct regmap_config const*) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int st_sensors_configure_spi_3_wire (struct spi_device*,TYPE_2__*) ; 
 scalar_t__ st_sensors_is_spi_3_wire (struct spi_device*) ; 
 struct regmap_config st_sensors_spi_regmap_config ; 
 struct regmap_config st_sensors_spi_regmap_multiread_bit_config ; 

int st_sensors_spi_configure(struct iio_dev *indio_dev,
			     struct spi_device *spi)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	const struct regmap_config *config;
	int err;

	if (st_sensors_is_spi_3_wire(spi)) {
		err = st_sensors_configure_spi_3_wire(spi,
						      sdata->sensor_settings);
		if (err < 0)
			return err;
	}

	if (sdata->sensor_settings->multi_read_bit)
		config = &st_sensors_spi_regmap_multiread_bit_config;
	else
		config = &st_sensors_spi_regmap_config;

	sdata->regmap = devm_regmap_init_spi(spi, config);
	if (IS_ERR(sdata->regmap)) {
		dev_err(&spi->dev, "Failed to register spi regmap (%d)\n",
			(int)PTR_ERR(sdata->regmap));
		return PTR_ERR(sdata->regmap);
	}

	spi_set_drvdata(spi, indio_dev);

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi->modalias;

	sdata->dev = &spi->dev;
	sdata->irq = spi->irq;

	return 0;
}