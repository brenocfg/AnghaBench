#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spi_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_2__ dev; } ;
struct TYPE_6__ {TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct ad7124_state {int /*<<< orphan*/ * vref; int /*<<< orphan*/  mclk; int /*<<< orphan*/  sd; int /*<<< orphan*/ * chip_info; } ;

/* Variables and functions */
 int AD7124_INT_REF ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ad7124_chip_info_tbl ; 
 int /*<<< orphan*/  ad7124_info ; 
 int ad7124_of_parse_channel_config (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ad7124_ref_names ; 
 int ad7124_setup (struct ad7124_state*) ; 
 int /*<<< orphan*/  ad7124_sigma_delta_info ; 
 int ad7124_soft_reset (struct ad7124_state*) ; 
 int /*<<< orphan*/  ad_sd_cleanup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  ad_sd_init (int /*<<< orphan*/ *,struct iio_dev*,struct spi_device*,int /*<<< orphan*/ *) ; 
 int ad_sd_setup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  devm_regulator_get_optional (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad7124_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad7124_probe(struct spi_device *spi)
{
	const struct spi_device_id *id;
	struct ad7124_state *st;
	struct iio_dev *indio_dev;
	int i, ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	id = spi_get_device_id(spi);
	st->chip_info = &ad7124_chip_info_tbl[id->driver_data];

	ad_sd_init(&st->sd, indio_dev, spi, &ad7124_sigma_delta_info);

	spi_set_drvdata(spi, indio_dev);

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &ad7124_info;

	ret = ad7124_of_parse_channel_config(indio_dev, spi->dev.of_node);
	if (ret < 0)
		return ret;

	for (i = 0; i < ARRAY_SIZE(st->vref); i++) {
		if (i == AD7124_INT_REF)
			continue;

		st->vref[i] = devm_regulator_get_optional(&spi->dev,
						ad7124_ref_names[i]);
		if (PTR_ERR(st->vref[i]) == -ENODEV)
			continue;
		else if (IS_ERR(st->vref[i]))
			return PTR_ERR(st->vref[i]);

		ret = regulator_enable(st->vref[i]);
		if (ret)
			return ret;
	}

	st->mclk = devm_clk_get(&spi->dev, "mclk");
	if (IS_ERR(st->mclk)) {
		ret = PTR_ERR(st->mclk);
		goto error_regulator_disable;
	}

	ret = clk_prepare_enable(st->mclk);
	if (ret < 0)
		goto error_regulator_disable;

	ret = ad7124_soft_reset(st);
	if (ret < 0)
		goto error_clk_disable_unprepare;

	ret = ad7124_setup(st);
	if (ret < 0)
		goto error_clk_disable_unprepare;

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	if (ret < 0)
		goto error_clk_disable_unprepare;

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(&spi->dev, "Failed to register iio device\n");
		goto error_remove_trigger;
	}

	return 0;

error_remove_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_clk_disable_unprepare:
	clk_disable_unprepare(st->mclk);
error_regulator_disable:
	for (i = ARRAY_SIZE(st->vref) - 1; i >= 0; i--) {
		if (!IS_ERR_OR_NULL(st->vref[i]))
			regulator_disable(st->vref[i]);
	}

	return ret;
}