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
struct mma7455_data {struct regmap* regmap; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/ * info; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  MMA7455_MCTL_MODE_MEASURE ; 
 int /*<<< orphan*/  MMA7455_REG_MCTL ; 
 int /*<<< orphan*/  MMA7455_REG_WHOAMI ; 
 unsigned int MMA7455_WHOAMI_ID ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mma7455_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mma7455_channels ; 
 int /*<<< orphan*/  mma7455_info ; 
 int /*<<< orphan*/  mma7455_scan_masks ; 
 int /*<<< orphan*/  mma7455_trigger_handler ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mma7455_core_probe(struct device *dev, struct regmap *regmap,
		       const char *name)
{
	struct mma7455_data *mma7455;
	struct iio_dev *indio_dev;
	unsigned int reg;
	int ret;

	ret = regmap_read(regmap, MMA7455_REG_WHOAMI, &reg);
	if (ret) {
		dev_err(dev, "unable to read reg\n");
		return ret;
	}

	if (reg != MMA7455_WHOAMI_ID) {
		dev_err(dev, "device id mismatch\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(dev, sizeof(*mma7455));
	if (!indio_dev)
		return -ENOMEM;

	dev_set_drvdata(dev, indio_dev);
	mma7455 = iio_priv(indio_dev);
	mma7455->regmap = regmap;

	indio_dev->info = &mma7455_info;
	indio_dev->name = name;
	indio_dev->dev.parent = dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = mma7455_channels;
	indio_dev->num_channels = ARRAY_SIZE(mma7455_channels);
	indio_dev->available_scan_masks = mma7455_scan_masks;

	regmap_write(mma7455->regmap, MMA7455_REG_MCTL,
		     MMA7455_MCTL_MODE_MEASURE);

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 mma7455_trigger_handler, NULL);
	if (ret) {
		dev_err(dev, "unable to setup triggered buffer\n");
		return ret;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(dev, "unable to register device\n");
		iio_triggered_buffer_cleanup(indio_dev);
		return ret;
	}

	return 0;
}