#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct regmap {int dummy; } ;
struct mpu3050 {int divisor; TYPE_2__* regs; int /*<<< orphan*/  orientation; int /*<<< orphan*/  lpf; int /*<<< orphan*/  fullscale; int /*<<< orphan*/  lock; struct regmap* map; struct device* dev; } ;
struct TYPE_5__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  modes; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; TYPE_2__* channels; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FS_2000_DPS ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 unsigned int MPU3050_CHIP_ID ; 
 unsigned int MPU3050_CHIP_ID_MASK ; 
 int /*<<< orphan*/  MPU3050_CHIP_ID_REG ; 
 int /*<<< orphan*/  MPU3050_DLPF_CFG_188HZ ; 
 int /*<<< orphan*/  MPU3050_PRODUCT_ID_REG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct mpu3050* iio_priv (struct iio_dev*) ; 
 int iio_read_mount_matrix (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpu3050_buffer_setup_ops ; 
 TYPE_2__* mpu3050_channels ; 
 int mpu3050_hw_init (struct mpu3050*) ; 
 int /*<<< orphan*/  mpu3050_info ; 
 int /*<<< orphan*/  mpu3050_power_down (struct mpu3050*) ; 
 int mpu3050_power_up (struct mpu3050*) ; 
 int /*<<< orphan*/  mpu3050_reg_vdd ; 
 int /*<<< orphan*/  mpu3050_reg_vlogic ; 
 int /*<<< orphan*/  mpu3050_scan_masks ; 
 int /*<<< orphan*/  mpu3050_trigger_handler ; 
 int mpu3050_trigger_probe (struct iio_dev*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

int mpu3050_common_probe(struct device *dev,
			 struct regmap *map,
			 int irq,
			 const char *name)
{
	struct iio_dev *indio_dev;
	struct mpu3050 *mpu3050;
	unsigned int val;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*mpu3050));
	if (!indio_dev)
		return -ENOMEM;
	mpu3050 = iio_priv(indio_dev);

	mpu3050->dev = dev;
	mpu3050->map = map;
	mutex_init(&mpu3050->lock);
	/* Default fullscale: 2000 degrees per second */
	mpu3050->fullscale = FS_2000_DPS;
	/* 1 kHz, divide by 100, default frequency = 10 Hz */
	mpu3050->lpf = MPU3050_DLPF_CFG_188HZ;
	mpu3050->divisor = 99;

	/* Read the mounting matrix, if present */
	ret = iio_read_mount_matrix(dev, "mount-matrix", &mpu3050->orientation);
	if (ret)
		return ret;

	/* Fetch and turn on regulators */
	mpu3050->regs[0].supply = mpu3050_reg_vdd;
	mpu3050->regs[1].supply = mpu3050_reg_vlogic;
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(mpu3050->regs),
				      mpu3050->regs);
	if (ret) {
		dev_err(dev, "Cannot get regulators\n");
		return ret;
	}

	ret = mpu3050_power_up(mpu3050);
	if (ret)
		return ret;

	ret = regmap_read(map, MPU3050_CHIP_ID_REG, &val);
	if (ret) {
		dev_err(dev, "could not read device ID\n");
		ret = -ENODEV;

		goto err_power_down;
	}

	if ((val & MPU3050_CHIP_ID_MASK) != MPU3050_CHIP_ID) {
		dev_err(dev, "unsupported chip id %02x\n",
				(u8)(val & MPU3050_CHIP_ID_MASK));
		ret = -ENODEV;
		goto err_power_down;
	}

	ret = regmap_read(map, MPU3050_PRODUCT_ID_REG, &val);
	if (ret) {
		dev_err(dev, "could not read device ID\n");
		ret = -ENODEV;

		goto err_power_down;
	}
	dev_info(dev, "found MPU-3050 part no: %d, version: %d\n",
		 ((val >> 4) & 0xf), (val & 0xf));

	ret = mpu3050_hw_init(mpu3050);
	if (ret)
		goto err_power_down;

	indio_dev->dev.parent = dev;
	indio_dev->channels = mpu3050_channels;
	indio_dev->num_channels = ARRAY_SIZE(mpu3050_channels);
	indio_dev->info = &mpu3050_info;
	indio_dev->available_scan_masks = mpu3050_scan_masks;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->name = name;

	ret = iio_triggered_buffer_setup(indio_dev, iio_pollfunc_store_time,
					 mpu3050_trigger_handler,
					 &mpu3050_buffer_setup_ops);
	if (ret) {
		dev_err(dev, "triggered buffer setup failed\n");
		goto err_power_down;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(dev, "device register failed\n");
		goto err_cleanup_buffer;
	}

	dev_set_drvdata(dev, indio_dev);

	/* Check if we have an assigned IRQ to use as trigger */
	if (irq) {
		ret = mpu3050_trigger_probe(indio_dev, irq);
		if (ret)
			dev_err(dev, "failed to register trigger\n");
	}

	/* Enable runtime PM */
	pm_runtime_get_noresume(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	/*
	 * Set autosuspend to two orders of magnitude larger than the
	 * start-up time. 100ms start-up time means 10000ms autosuspend,
	 * i.e. 10 seconds.
	 */
	pm_runtime_set_autosuspend_delay(dev, 10000);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_put(dev);

	return 0;

err_cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
err_power_down:
	mpu3050_power_down(mpu3050);

	return ret;
}