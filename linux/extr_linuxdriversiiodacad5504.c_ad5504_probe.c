#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct ad5504_platform_data* platform_data; } ;
struct spi_device {scalar_t__ irq; TYPE_3__ dev; } ;
struct regulator {int dummy; } ;
struct TYPE_7__ {TYPE_3__* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct ad5504_state {int vref_mv; struct spi_device* spi; struct regulator* reg; } ;
struct ad5504_platform_data {int vref_mv; } ;
struct TYPE_8__ {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ ID_AD5501 ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  IS_ERR (struct regulator*) ; 
 int /*<<< orphan*/  ad5504_channels ; 
 int /*<<< orphan*/  ad5504_event_handler ; 
 int /*<<< orphan*/  ad5504_info ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 struct regulator* devm_regulator_get (TYPE_3__*,char*) ; 
 int devm_request_threaded_irq (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad5504_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (struct regulator*) ; 
 int regulator_enable (struct regulator*) ; 
 int regulator_get_voltage (struct regulator*) ; 
 TYPE_2__* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int ad5504_probe(struct spi_device *spi)
{
	struct ad5504_platform_data *pdata = spi->dev.platform_data;
	struct iio_dev *indio_dev;
	struct ad5504_state *st;
	struct regulator *reg;
	int ret, voltage_uv = 0;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;
	reg = devm_regulator_get(&spi->dev, "vcc");
	if (!IS_ERR(reg)) {
		ret = regulator_enable(reg);
		if (ret)
			return ret;

		ret = regulator_get_voltage(reg);
		if (ret < 0)
			goto error_disable_reg;

		voltage_uv = ret;
	}

	spi_set_drvdata(spi, indio_dev);
	st = iio_priv(indio_dev);
	if (voltage_uv)
		st->vref_mv = voltage_uv / 1000;
	else if (pdata)
		st->vref_mv = pdata->vref_mv;
	else
		dev_warn(&spi->dev, "reference voltage unspecified\n");

	st->reg = reg;
	st->spi = spi;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->name = spi_get_device_id(st->spi)->name;
	indio_dev->info = &ad5504_info;
	if (spi_get_device_id(st->spi)->driver_data == ID_AD5501)
		indio_dev->num_channels = 1;
	else
		indio_dev->num_channels = 4;
	indio_dev->channels = ad5504_channels;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (spi->irq) {
		ret = devm_request_threaded_irq(&spi->dev, spi->irq,
					   NULL,
					   &ad5504_event_handler,
					   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					   spi_get_device_id(st->spi)->name,
					   indio_dev);
		if (ret)
			goto error_disable_reg;
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_disable_reg;

	return 0;

error_disable_reg:
	if (!IS_ERR(reg))
		regulator_disable(reg);

	return ret;
}