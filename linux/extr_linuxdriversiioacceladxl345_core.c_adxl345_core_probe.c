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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct adxl345_data {int type; struct regmap* regmap; int /*<<< orphan*/  data_range; } ;
typedef  enum adxl345_device_type { ____Placeholder_adxl345_device_type } adxl345_device_type ;

/* Variables and functions */
 int /*<<< orphan*/  ADXL345_DATA_FORMAT_FULL_RES ; 
 int /*<<< orphan*/  ADXL345_DEVID ; 
 int /*<<< orphan*/  ADXL345_POWER_CTL_MEASURE ; 
 int /*<<< orphan*/  ADXL345_POWER_CTL_STANDBY ; 
 int /*<<< orphan*/  ADXL345_REG_DATA_FORMAT ; 
 int /*<<< orphan*/  ADXL345_REG_DEVID ; 
 int /*<<< orphan*/  ADXL345_REG_POWER_CTL ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  adxl345_channels ; 
 int /*<<< orphan*/  adxl345_info ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct adxl345_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int adxl345_core_probe(struct device *dev, struct regmap *regmap,
		       enum adxl345_device_type type, const char *name)
{
	struct adxl345_data *data;
	struct iio_dev *indio_dev;
	u32 regval;
	int ret;

	ret = regmap_read(regmap, ADXL345_REG_DEVID, &regval);
	if (ret < 0) {
		dev_err(dev, "Error reading device ID: %d\n", ret);
		return ret;
	}

	if (regval != ADXL345_DEVID) {
		dev_err(dev, "Invalid device ID: %x, expected %x\n",
			regval, ADXL345_DEVID);
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;
	data->type = type;
	/* Enable full-resolution mode */
	data->data_range = ADXL345_DATA_FORMAT_FULL_RES;

	ret = regmap_write(data->regmap, ADXL345_REG_DATA_FORMAT,
			   data->data_range);
	if (ret < 0) {
		dev_err(dev, "Failed to set data range: %d\n", ret);
		return ret;
	}

	indio_dev->dev.parent = dev;
	indio_dev->name = name;
	indio_dev->info = &adxl345_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = adxl345_channels;
	indio_dev->num_channels = ARRAY_SIZE(adxl345_channels);

	/* Enable measurement mode */
	ret = regmap_write(data->regmap, ADXL345_REG_POWER_CTL,
			   ADXL345_POWER_CTL_MEASURE);
	if (ret < 0) {
		dev_err(dev, "Failed to enable measurement mode: %d\n", ret);
		return ret;
	}

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(dev, "iio_device_register failed: %d\n", ret);
		regmap_write(data->regmap, ADXL345_REG_POWER_CTL,
			     ADXL345_POWER_CTL_STANDBY);
	}

	return ret;
}