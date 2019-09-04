#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct ad9523_platform_data* platform_data; } ;
struct spi_device {TYPE_3__ dev; } ;
struct TYPE_8__ {TYPE_3__* parent; } ;
struct iio_dev {scalar_t__* name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct ad9523_state {void* reg; int /*<<< orphan*/  ad9523_channels; struct ad9523_platform_data* pdata; struct spi_device* spi; void* sync_gpio; void* reset_gpio; void* pwrdown_gpio; int /*<<< orphan*/  lock; } ;
struct ad9523_platform_data {scalar_t__* name; int /*<<< orphan*/  num_channels; } ;
struct TYPE_9__ {scalar_t__* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ad9523_info ; 
 int ad9523_setup (struct iio_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,scalar_t__*) ; 
 void* devm_gpiod_get_optional (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 void* devm_regulator_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  gpiod_direction_output (void*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad9523_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ad9523_probe(struct spi_device *spi)
{
	struct ad9523_platform_data *pdata = spi->dev.platform_data;
	struct iio_dev *indio_dev;
	struct ad9523_state *st;
	int ret;

	if (!pdata) {
		dev_err(&spi->dev, "no platform data?\n");
		return -EINVAL;
	}

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (indio_dev == NULL)
		return -ENOMEM;

	st = iio_priv(indio_dev);

	mutex_init(&st->lock);

	st->reg = devm_regulator_get(&spi->dev, "vcc");
	if (!IS_ERR(st->reg)) {
		ret = regulator_enable(st->reg);
		if (ret)
			return ret;
	}

	st->pwrdown_gpio = devm_gpiod_get_optional(&spi->dev, "powerdown",
		GPIOD_OUT_HIGH);
	if (IS_ERR(st->pwrdown_gpio)) {
		ret = PTR_ERR(st->pwrdown_gpio);
		goto error_disable_reg;
	}

	st->reset_gpio = devm_gpiod_get_optional(&spi->dev, "reset",
		GPIOD_OUT_LOW);
	if (IS_ERR(st->reset_gpio)) {
		ret = PTR_ERR(st->reset_gpio);
		goto error_disable_reg;
	}

	if (st->reset_gpio) {
		udelay(1);
		gpiod_direction_output(st->reset_gpio, 1);
	}

	st->sync_gpio = devm_gpiod_get_optional(&spi->dev, "sync",
		GPIOD_OUT_HIGH);
	if (IS_ERR(st->sync_gpio)) {
		ret = PTR_ERR(st->sync_gpio);
		goto error_disable_reg;
	}

	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;
	st->pdata = pdata;

	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = (pdata->name[0] != 0) ? pdata->name :
			  spi_get_device_id(spi)->name;
	indio_dev->info = &ad9523_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = st->ad9523_channels;
	indio_dev->num_channels = pdata->num_channels;

	ret = ad9523_setup(indio_dev);
	if (ret < 0)
		goto error_disable_reg;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_disable_reg;

	dev_info(&spi->dev, "probed %s\n", indio_dev->name);

	return 0;

error_disable_reg:
	if (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	return ret;
}