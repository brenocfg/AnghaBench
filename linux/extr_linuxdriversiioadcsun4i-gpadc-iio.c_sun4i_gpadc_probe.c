#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sun4i_gpadc_iio {int /*<<< orphan*/  no_irq; int /*<<< orphan*/  tzd; int /*<<< orphan*/  sensor_device; int /*<<< orphan*/  completion; struct iio_dev* indio_dev; int /*<<< orphan*/  mutex; } ;
struct TYPE_13__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_12__ {scalar_t__ of_node; TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THERMAL_OF ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_GPADC_AUTOSUSPEND_DELAY ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_map_array_unregister (struct iio_dev*) ; 
 struct sun4i_gpadc_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  sun4i_gpadc_iio_info ; 
 int sun4i_gpadc_probe_dt (struct platform_device*,struct iio_dev*) ; 
 int sun4i_gpadc_probe_mfd (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  sun4i_ts_tz_ops ; 
 int /*<<< orphan*/  thermal_zone_of_sensor_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sun4i_gpadc_iio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun4i_gpadc_probe(struct platform_device *pdev)
{
	struct sun4i_gpadc_iio *info;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*info));
	if (!indio_dev)
		return -ENOMEM;

	info = iio_priv(indio_dev);
	platform_set_drvdata(pdev, indio_dev);

	mutex_init(&info->mutex);
	info->indio_dev = indio_dev;
	init_completion(&info->completion);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &sun4i_gpadc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (pdev->dev.of_node)
		ret = sun4i_gpadc_probe_dt(pdev, indio_dev);
	else
		ret = sun4i_gpadc_probe_mfd(pdev, indio_dev);

	if (ret)
		return ret;

	pm_runtime_set_autosuspend_delay(&pdev->dev,
					 SUN4I_GPADC_AUTOSUSPEND_DELAY);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	if (IS_ENABLED(CONFIG_THERMAL_OF)) {
		info->tzd = thermal_zone_of_sensor_register(info->sensor_device,
							    0, info,
							    &sun4i_ts_tz_ops);
		/*
		 * Do not fail driver probing when failing to register in
		 * thermal because no thermal DT node is found.
		 */
		if (IS_ERR(info->tzd) && PTR_ERR(info->tzd) != -ENODEV) {
			dev_err(&pdev->dev,
				"could not register thermal sensor: %ld\n",
				PTR_ERR(info->tzd));
			return PTR_ERR(info->tzd);
		}
	}

	ret = devm_iio_device_register(&pdev->dev, indio_dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not register the device\n");
		goto err_map;
	}

	return 0;

err_map:
	if (!info->no_irq && IS_ENABLED(CONFIG_THERMAL_OF))
		iio_map_array_unregister(indio_dev);

	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return ret;
}