#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_3__ dev; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct ads8688_state {int vref_mv; int /*<<< orphan*/  reg; int /*<<< orphan*/  lock; TYPE_6__* chip_info; struct spi_device* spi; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct TYPE_8__ {size_t driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ADS8688_VREF_MV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_MODE_1 ; 
 TYPE_6__* ads8688_chip_info_tbl ; 
 int /*<<< orphan*/  ads8688_info ; 
 int /*<<< orphan*/  ads8688_reset (struct iio_dev*) ; 
 int /*<<< orphan*/  ads8688_trigger_handler ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  devm_regulator_get_optional (TYPE_3__*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ads8688_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ads8688_probe(struct spi_device *spi)
{
	struct ads8688_state *st;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (indio_dev == NULL)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get_optional(&spi->dev, "vref");
	if (!IS_ERR(st->reg)) {
		ret = regulator_enable(st->reg);
		if (ret)
			return ret;

		ret = regulator_get_voltage(st->reg);
		if (ret < 0)
			goto err_regulator_disable;

		st->vref_mv = ret / 1000;
	} else {
		/* Use internal reference */
		st->vref_mv = ADS8688_VREF_MV;
	}

	st->chip_info =	&ads8688_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	spi->mode = SPI_MODE_1;

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->dev.of_node = spi->dev.of_node;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->info = &ads8688_info;

	ads8688_reset(indio_dev);

	mutex_init(&st->lock);

	ret = iio_triggered_buffer_setup(indio_dev, NULL, ads8688_trigger_handler, NULL);
	if (ret < 0) {
		dev_err(&spi->dev, "iio triggered buffer setup failed\n");
		goto err_regulator_disable;
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err_buffer_cleanup;

	return 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);

err_regulator_disable:
	if (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	return ret;
}