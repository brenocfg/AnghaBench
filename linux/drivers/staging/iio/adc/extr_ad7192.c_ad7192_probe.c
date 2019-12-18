#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {TYPE_4__ dev; int /*<<< orphan*/  irq; } ;
struct TYPE_8__ {TYPE_4__* parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_12__ {TYPE_2__* spi; } ;
struct ad7192_state {int int_vref_mv; scalar_t__ devid; scalar_t__ clock_sel; void* avdd; void* dvdd; void* mclk; int /*<<< orphan*/  fclk; TYPE_7__ sd; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AD7192_CLK_EXT_MCLK1_2 ; 
 scalar_t__ AD7192_CLK_EXT_MCLK2 ; 
 int /*<<< orphan*/  AD7192_INT_FREQ_MHZ ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ ID_AD7195 ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int ad7192_channels_config (struct iio_dev*) ; 
 int /*<<< orphan*/  ad7192_info ; 
 scalar_t__ ad7192_of_clock_select (struct ad7192_state*) ; 
 int ad7192_setup (struct ad7192_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad7192_sigma_delta_info ; 
 int /*<<< orphan*/  ad7192_valid_external_frequency (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad7195_info ; 
 int /*<<< orphan*/  ad_sd_cleanup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  ad_sd_init (TYPE_7__*,struct iio_dev*,struct spi_device*,int /*<<< orphan*/ *) ; 
 int ad_sd_setup_buffer_and_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int /*<<< orphan*/  clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_4__*,int) ; 
 void* devm_regulator_get (TYPE_4__*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad7192_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 int regulator_get_voltage (void*) ; 
 TYPE_3__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad7192_probe(struct spi_device *spi)
{
	struct ad7192_state *st;
	struct iio_dev *indio_dev;
	int ret, voltage_uv = 0;

	if (!spi->irq) {
		dev_err(&spi->dev, "no IRQ?\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	mutex_init(&st->lock);

	st->avdd = devm_regulator_get(&spi->dev, "avdd");
	if (IS_ERR(st->avdd))
		return PTR_ERR(st->avdd);

	ret = regulator_enable(st->avdd);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified AVdd supply\n");
		return ret;
	}

	st->dvdd = devm_regulator_get(&spi->dev, "dvdd");
	if (IS_ERR(st->dvdd)) {
		ret = PTR_ERR(st->dvdd);
		goto error_disable_avdd;
	}

	ret = regulator_enable(st->dvdd);
	if (ret) {
		dev_err(&spi->dev, "Failed to enable specified DVdd supply\n");
		goto error_disable_avdd;
	}

	voltage_uv = regulator_get_voltage(st->avdd);

	if (voltage_uv)
		st->int_vref_mv = voltage_uv / 1000;
	else
		dev_err(&spi->dev, "Device tree error, reference voltage undefined\n");

	spi_set_drvdata(spi, indio_dev);
	st->devid = spi_get_device_id(spi)->driver_data;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = ad7192_channels_config(indio_dev);
	if (ret < 0)
		goto error_disable_dvdd;

	if (st->devid == ID_AD7195)
		indio_dev->info = &ad7195_info;
	else
		indio_dev->info = &ad7192_info;

	ad_sd_init(&st->sd, indio_dev, spi, &ad7192_sigma_delta_info);

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	if (ret)
		goto error_disable_dvdd;

	st->fclk = AD7192_INT_FREQ_MHZ;

	st->mclk = devm_clk_get(&st->sd.spi->dev, "mclk");
	if (IS_ERR(st->mclk) && PTR_ERR(st->mclk) != -ENOENT) {
		ret = PTR_ERR(st->mclk);
		goto error_remove_trigger;
	}

	st->clock_sel = ad7192_of_clock_select(st);

	if (st->clock_sel == AD7192_CLK_EXT_MCLK1_2 ||
	    st->clock_sel == AD7192_CLK_EXT_MCLK2) {
		ret = clk_prepare_enable(st->mclk);
		if (ret < 0)
			goto error_remove_trigger;

		st->fclk = clk_get_rate(st->mclk);
		if (!ad7192_valid_external_frequency(st->fclk)) {
			ret = -EINVAL;
			dev_err(&spi->dev,
				"External clock frequency out of bounds\n");
			goto error_disable_clk;
		}
	}

	ret = ad7192_setup(st, spi->dev.of_node);
	if (ret)
		goto error_disable_clk;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto error_disable_clk;
	return 0;

error_disable_clk:
	clk_disable_unprepare(st->mclk);
error_remove_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_disable_dvdd:
	regulator_disable(st->dvdd);
error_disable_avdd:
	regulator_disable(st->avdd);

	return ret;
}