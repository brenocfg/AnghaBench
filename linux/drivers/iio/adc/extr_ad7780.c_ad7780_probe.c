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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/ * info; int /*<<< orphan*/ * channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct ad7780_state {int gain; int /*<<< orphan*/  reg; TYPE_3__* chip_info; int /*<<< orphan*/  sd; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel; } ;
struct TYPE_5__ {size_t driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_3__* ad7780_chip_info_tbl ; 
 int /*<<< orphan*/  ad7780_info ; 
 int ad7780_init_gpios (int /*<<< orphan*/ *,struct ad7780_state*) ; 
 int /*<<< orphan*/  ad7780_sigma_delta_info ; 
 int /*<<< orphan*/  ad_sd_cleanup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  ad_sd_init (int /*<<< orphan*/ *,struct iio_dev*,struct spi_device*,int /*<<< orphan*/ *) ; 
 int ad_sd_setup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad7780_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad7780_probe(struct spi_device *spi)
{
	struct ad7780_state *st;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	st->gain = 1;

	ad_sd_init(&st->sd, indio_dev, spi, &ad7780_sigma_delta_info);

	st->chip_info =
		&ad7780_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	spi_set_drvdata(spi, indio_dev);

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = &st->chip_info->channel;
	indio_dev->num_channels = 1;
	indio_dev->info = &ad7780_info;

	ret = ad7780_init_gpios(&spi->dev, st);
	if (ret)
		goto error_cleanup_buffer_and_trigger;

	st->reg = devm_regulator_get(&spi->dev, "avdd");
	if (IS_ERR(st->reg))
		return PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified AVdd supply\n");
		return ret;
	}

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	if (ret)
		goto error_disable_reg;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_cleanup_buffer_and_trigger;

	return 0;

error_cleanup_buffer_and_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_disable_reg:
	regulator_disable(st->reg);

	return ret;
}