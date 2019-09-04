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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct ltc2632_state {int vref_mv; int /*<<< orphan*/ * vref_reg; struct spi_device* spi_dev; } ;
struct ltc2632_chip_info {int vref_mv; int /*<<< orphan*/  channels; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LTC2632_CMD_EXTERNAL_REFER ; 
 int /*<<< orphan*/  LTC2632_CMD_INTERNAL_REFER ; 
 int /*<<< orphan*/  LTC2632_DAC_CHANNELS ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_3__* dev_of_node (int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ltc2632_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ltc2632_info ; 
 int ltc2632_spi_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int regulator_get_voltage (int /*<<< orphan*/ *) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ltc2632_probe(struct spi_device *spi)
{
	struct ltc2632_state *st;
	struct iio_dev *indio_dev;
	struct ltc2632_chip_info *chip_info;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	spi_set_drvdata(spi, indio_dev);
	st->spi_dev = spi;

	chip_info = (struct ltc2632_chip_info *)
			spi_get_device_id(spi)->driver_data;

	st->vref_reg = devm_regulator_get_optional(&spi->dev, "vref");
	if (PTR_ERR(st->vref_reg) == -ENODEV) {
		/* use internal reference voltage */
		st->vref_reg = NULL;
		st->vref_mv = chip_info->vref_mv;

		ret = ltc2632_spi_write(spi, LTC2632_CMD_INTERNAL_REFER,
				0, 0, 0);
		if (ret) {
			dev_err(&spi->dev,
				"Set internal reference command failed, %d\n",
				ret);
			return ret;
		}
	} else if (IS_ERR(st->vref_reg)) {
		dev_err(&spi->dev,
				"Error getting voltage reference regulator\n");
		return PTR_ERR(st->vref_reg);
	} else {
		/* use external reference voltage */
		ret = regulator_enable(st->vref_reg);
		if (ret) {
			dev_err(&spi->dev,
				"enable reference regulator failed, %d\n",
				ret);
			return ret;
		}
		st->vref_mv = regulator_get_voltage(st->vref_reg) / 1000;

		ret = ltc2632_spi_write(spi, LTC2632_CMD_EXTERNAL_REFER,
				0, 0, 0);
		if (ret) {
			dev_err(&spi->dev,
				"Set external reference command failed, %d\n",
				ret);
			return ret;
		}
	}

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = dev_of_node(&spi->dev) ? dev_of_node(&spi->dev)->name
						 : spi_get_device_id(spi)->name;
	indio_dev->info = &ltc2632_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = chip_info->channels;
	indio_dev->num_channels = LTC2632_DAC_CHANNELS;

	return iio_device_register(indio_dev);
}