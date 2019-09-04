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
struct regmap {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct bmi160_data {struct regmap* regmap; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  bmi160_channels ; 
 int bmi160_chip_init (struct bmi160_data*,int) ; 
 int /*<<< orphan*/  bmi160_chip_uninit (struct bmi160_data*) ; 
 int /*<<< orphan*/  bmi160_info ; 
 char* bmi160_match_acpi_device (struct device*) ; 
 int /*<<< orphan*/  bmi160_trigger_handler ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct bmi160_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bmi160_core_probe(struct device *dev, struct regmap *regmap,
		      const char *name, bool use_spi)
{
	struct iio_dev *indio_dev;
	struct bmi160_data *data;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;

	ret = bmi160_chip_init(data, use_spi);
	if (ret < 0)
		return ret;

	if (!name && ACPI_HANDLE(dev))
		name = bmi160_match_acpi_device(dev);

	indio_dev->dev.parent = dev;
	indio_dev->channels = bmi160_channels;
	indio_dev->num_channels = ARRAY_SIZE(bmi160_channels);
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &bmi160_info;

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 bmi160_trigger_handler, NULL);
	if (ret < 0)
		goto uninit;

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto buffer_cleanup;

	return 0;
buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
uninit:
	bmi160_chip_uninit(data);
	return ret;
}