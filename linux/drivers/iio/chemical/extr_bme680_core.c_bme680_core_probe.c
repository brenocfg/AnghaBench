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
struct iio_dev {char const* name; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct bme680_data {int oversampling_humid; int oversampling_press; int oversampling_temp; int heater_temp; int heater_dur; int /*<<< orphan*/  bme680; struct regmap* regmap; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int BME680_CHIP_ID_VAL ; 
 int /*<<< orphan*/  BME680_CMD_SOFTRESET ; 
 int /*<<< orphan*/  BME680_REG_CHIP_ID ; 
 int /*<<< orphan*/  BME680_REG_SOFT_RESET ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  bme680_channels ; 
 int bme680_chip_config (struct bme680_data*) ; 
 int bme680_gas_config (struct bme680_data*) ; 
 int /*<<< orphan*/  bme680_info ; 
 char* bme680_match_acpi_device (struct device*) ; 
 int bme680_read_calib (struct bme680_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 struct bme680_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bme680_core_probe(struct device *dev, struct regmap *regmap,
		      const char *name)
{
	struct iio_dev *indio_dev;
	struct bme680_data *data;
	unsigned int val;
	int ret;

	ret = regmap_write(regmap, BME680_REG_SOFT_RESET,
			   BME680_CMD_SOFTRESET);
	if (ret < 0) {
		dev_err(dev, "Failed to reset chip\n");
		return ret;
	}

	ret = regmap_read(regmap, BME680_REG_CHIP_ID, &val);
	if (ret < 0) {
		dev_err(dev, "Error reading chip ID\n");
		return ret;
	}

	if (val != BME680_CHIP_ID_VAL) {
		dev_err(dev, "Wrong chip ID, got %x expected %x\n",
				val, BME680_CHIP_ID_VAL);
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	if (!name && ACPI_HANDLE(dev))
		name = bme680_match_acpi_device(dev);

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;
	indio_dev->dev.parent = dev;
	indio_dev->name = name;
	indio_dev->channels = bme680_channels;
	indio_dev->num_channels = ARRAY_SIZE(bme680_channels);
	indio_dev->info = &bme680_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	/* default values for the sensor */
	data->oversampling_humid = 2; /* 2X oversampling rate */
	data->oversampling_press = 4; /* 4X oversampling rate */
	data->oversampling_temp = 8;  /* 8X oversampling rate */
	data->heater_temp = 320; /* degree Celsius */
	data->heater_dur = 150;  /* milliseconds */

	ret = bme680_chip_config(data);
	if (ret < 0) {
		dev_err(dev, "failed to set chip_config data\n");
		return ret;
	}

	ret = bme680_gas_config(data);
	if (ret < 0) {
		dev_err(dev, "failed to set gas config data\n");
		return ret;
	}

	ret = bme680_read_calib(data, &data->bme680);
	if (ret < 0) {
		dev_err(dev,
			"failed to read calibration coefficients at probe\n");
		return ret;
	}

	return devm_iio_device_register(dev, indio_dev);
}