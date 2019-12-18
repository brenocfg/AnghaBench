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
struct spi_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_2__ dev; } ;
struct TYPE_4__ {TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct adis16480 {int clk_freq; int /*<<< orphan*/  ext_clk; int /*<<< orphan*/  adis; TYPE_3__* chip_info; } ;
struct TYPE_6__ {int int_clk; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 TYPE_3__* adis16480_chip_info ; 
 int adis16480_config_irq_pin (int /*<<< orphan*/ ,struct adis16480*) ; 
 int /*<<< orphan*/  adis16480_data ; 
 int /*<<< orphan*/  adis16480_debugfs_init (struct iio_dev*) ; 
 int adis16480_ext_clk_config (struct adis16480*,int /*<<< orphan*/ ,int) ; 
 int adis16480_get_ext_clocks (struct adis16480*) ; 
 int /*<<< orphan*/  adis16480_info ; 
 int adis16480_initial_setup (struct iio_dev*) ; 
 int /*<<< orphan*/  adis16480_stop_device (struct iio_dev*) ; 
 int /*<<< orphan*/  adis_cleanup_buffer_and_trigger (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int adis_init (int /*<<< orphan*/ *,struct iio_dev*,struct spi_device*,int /*<<< orphan*/ *) ; 
 int adis_setup_buffer_and_trigger (int /*<<< orphan*/ *,struct iio_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct adis16480* iio_priv (struct iio_dev*) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int adis16480_probe(struct spi_device *spi)
{
	const struct spi_device_id *id = spi_get_device_id(spi);
	struct iio_dev *indio_dev;
	struct adis16480 *st;
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (indio_dev == NULL)
		return -ENOMEM;

	spi_set_drvdata(spi, indio_dev);

	st = iio_priv(indio_dev);

	st->chip_info = &adis16480_chip_info[id->driver_data];
	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->info = &adis16480_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = adis_init(&st->adis, indio_dev, spi, &adis16480_data);
	if (ret)
		return ret;

	ret = adis16480_config_irq_pin(spi->dev.of_node, st);
	if (ret)
		return ret;

	ret = adis16480_get_ext_clocks(st);
	if (ret)
		return ret;

	if (!IS_ERR_OR_NULL(st->ext_clk)) {
		ret = adis16480_ext_clk_config(st, spi->dev.of_node, true);
		if (ret)
			return ret;

		st->clk_freq = clk_get_rate(st->ext_clk);
		st->clk_freq *= 1000; /* micro */
	} else {
		st->clk_freq = st->chip_info->int_clk;
	}

	ret = adis_setup_buffer_and_trigger(&st->adis, indio_dev, NULL);
	if (ret)
		goto error_clk_disable_unprepare;

	ret = adis16480_initial_setup(indio_dev);
	if (ret)
		goto error_cleanup_buffer;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_stop_device;

	adis16480_debugfs_init(indio_dev);

	return 0;

error_stop_device:
	adis16480_stop_device(indio_dev);
error_cleanup_buffer:
	adis_cleanup_buffer_and_trigger(&st->adis, indio_dev);
error_clk_disable_unprepare:
	clk_disable_unprepare(st->ext_clk);
	return ret;
}