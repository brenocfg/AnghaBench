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
struct spi_device_id {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct max1118 {int /*<<< orphan*/  reg; int /*<<< orphan*/  lock; struct spi_device* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct max1118* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ max1118 ; 
 int /*<<< orphan*/  max1118_channels ; 
 int /*<<< orphan*/  max1118_info ; 
 int /*<<< orphan*/  max1118_read (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max1118_trigger_handler ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct spi_device_id* spi_get_device_id (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct iio_dev*) ; 

__attribute__((used)) static int max1118_probe(struct spi_device *spi)
{
	struct iio_dev *indio_dev;
	struct max1118 *adc;
	const struct spi_device_id *id = spi_get_device_id(spi);
	int ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->lock);

	if (id->driver_data == max1118) {
		adc->reg = devm_regulator_get(&spi->dev, "vref");
		if (IS_ERR(adc->reg)) {
			dev_err(&spi->dev, "failed to get vref regulator\n");
			return PTR_ERR(adc->reg);
		}
		ret = regulator_enable(adc->reg);
		if (ret)
			return ret;
	}

	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->info = &max1118_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = max1118_channels;
	indio_dev->num_channels = ARRAY_SIZE(max1118_channels);

	/*
	 * To reinitiate a conversion on CH0, it is necessary to allow for a
	 * conversion to be complete and all of the data to be read out.  Once
	 * a conversion has been completed, the MAX1117/MAX1118/MAX1119 will go
	 * into AutoShutdown mode until the next conversion is initiated.
	 */
	max1118_read(spi, 0);

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					max1118_trigger_handler, NULL);
	if (ret)
		goto err_reg_disable;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err_buffer_cleanup;

	return 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_reg_disable:
	if (id->driver_data == max1118)
		regulator_disable(adc->reg);

	return ret;
}