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
struct regmap {int dummy; } ;
struct kxsd9_state {int /*<<< orphan*/  scale; TYPE_2__* regs; int /*<<< orphan*/  orientation; struct regmap* map; struct device* dev; } ;
struct TYPE_5__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  num_channels; TYPE_2__* channels; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  KXSD9_CTRL_C_FS_2G ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct kxsd9_state* iio_priv (struct iio_dev*) ; 
 int iio_read_mount_matrix (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxsd9_buffer_setup_ops ; 
 TYPE_2__* kxsd9_channels ; 
 int /*<<< orphan*/  kxsd9_info ; 
 int /*<<< orphan*/  kxsd9_power_down (struct kxsd9_state*) ; 
 int /*<<< orphan*/  kxsd9_power_up (struct kxsd9_state*) ; 
 int /*<<< orphan*/  kxsd9_reg_iovdd ; 
 int /*<<< orphan*/  kxsd9_reg_vdd ; 
 int /*<<< orphan*/  kxsd9_scan_masks ; 
 int /*<<< orphan*/  kxsd9_trigger_handler ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

int kxsd9_common_probe(struct device *dev,
		       struct regmap *map,
		       const char *name)
{
	struct iio_dev *indio_dev;
	struct kxsd9_state *st;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	st->dev = dev;
	st->map = map;

	indio_dev->channels = kxsd9_channels;
	indio_dev->num_channels = ARRAY_SIZE(kxsd9_channels);
	indio_dev->name = name;
	indio_dev->dev.parent = dev;
	indio_dev->info = &kxsd9_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->available_scan_masks = kxsd9_scan_masks;

	/* Read the mounting matrix, if present */
	ret = iio_read_mount_matrix(dev, "mount-matrix", &st->orientation);
	if (ret)
		return ret;

	/* Fetch and turn on regulators */
	st->regs[0].supply = kxsd9_reg_vdd;
	st->regs[1].supply = kxsd9_reg_iovdd;
	ret = devm_regulator_bulk_get(dev,
				      ARRAY_SIZE(st->regs),
				      st->regs);
	if (ret) {
		dev_err(dev, "Cannot get regulators\n");
		return ret;
	}
	/* Default scaling */
	st->scale = KXSD9_CTRL_C_FS_2G;

	kxsd9_power_up(st);

	ret = iio_triggered_buffer_setup(indio_dev,
					 iio_pollfunc_store_time,
					 kxsd9_trigger_handler,
					 &kxsd9_buffer_setup_ops);
	if (ret) {
		dev_err(dev, "triggered buffer setup failed\n");
		goto err_power_down;
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err_cleanup_buffer;

	dev_set_drvdata(dev, indio_dev);

	/* Enable runtime PM */
	pm_runtime_get_noresume(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	/*
	 * Set autosuspend to two orders of magnitude larger than the
	 * start-up time. 20ms start-up time means 2000ms autosuspend,
	 * i.e. 2 seconds.
	 */
	pm_runtime_set_autosuspend_delay(dev, 2000);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_put(dev);

	return 0;

err_cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
err_power_down:
	kxsd9_power_down(st);

	return ret;
}