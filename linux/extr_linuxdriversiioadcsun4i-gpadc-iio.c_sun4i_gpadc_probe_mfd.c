#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sun4i_gpadc_iio {int no_irq; int /*<<< orphan*/  ignore_fifo_data_irq; int /*<<< orphan*/  fifo_data_irq; int /*<<< orphan*/  ignore_temp_data_irq; int /*<<< orphan*/  temp_data_irq; int /*<<< orphan*/  sensor_device; struct gpadc_data* data; int /*<<< orphan*/  regmap; } ;
struct sun4i_gpadc_dev {int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct iio_dev {void* channels; void* num_channels; } ;
struct gpadc_data {int dummy; } ;
struct TYPE_3__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CONFIG_THERMAL_OF ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 struct sun4i_gpadc_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int iio_map_array_register (struct iio_dev*,int /*<<< orphan*/ ) ; 
 struct sun4i_gpadc_iio* iio_priv (struct iio_dev*) ; 
 TYPE_1__* platform_get_device_id (struct platform_device*) ; 
 void* sun4i_gpadc_channels ; 
 void* sun4i_gpadc_channels_no_temp ; 
 int /*<<< orphan*/  sun4i_gpadc_fifo_data_irq_handler ; 
 int /*<<< orphan*/  sun4i_gpadc_hwmon_maps ; 
 int /*<<< orphan*/  sun4i_gpadc_temp_data_irq_handler ; 
 int sun4i_irq_init (struct platform_device*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun4i_gpadc_probe_mfd(struct platform_device *pdev,
				 struct iio_dev *indio_dev)
{
	struct sun4i_gpadc_iio *info = iio_priv(indio_dev);
	struct sun4i_gpadc_dev *sun4i_gpadc_dev =
		dev_get_drvdata(pdev->dev.parent);
	int ret;

	info->no_irq = false;
	info->regmap = sun4i_gpadc_dev->regmap;

	indio_dev->num_channels = ARRAY_SIZE(sun4i_gpadc_channels);
	indio_dev->channels = sun4i_gpadc_channels;

	info->data = (struct gpadc_data *)platform_get_device_id(pdev)->driver_data;

	/*
	 * Since the controller needs to be in touchscreen mode for its thermal
	 * sensor to operate properly, and that switching between the two modes
	 * needs a delay, always registering in the thermal framework will
	 * significantly slow down the conversion rate of the ADCs.
	 *
	 * Therefore, instead of depending on THERMAL_OF in Kconfig, we only
	 * register the sensor if that option is enabled, eventually leaving
	 * that choice to the user.
	 */

	if (IS_ENABLED(CONFIG_THERMAL_OF)) {
		/*
		 * This driver is a child of an MFD which has a node in the DT
		 * but not its children, because of DT backward compatibility
		 * for A10, A13 and A31 SoCs. Therefore, the resulting devices
		 * of this driver do not have an of_node variable.
		 * However, its parent (the MFD driver) has an of_node variable
		 * and since devm_thermal_zone_of_sensor_register uses its first
		 * argument to match the phandle defined in the node of the
		 * thermal driver with the of_node of the device passed as first
		 * argument and the third argument to call ops from
		 * thermal_zone_of_device_ops, the solution is to use the parent
		 * device as first argument to match the phandle with its
		 * of_node, and the device from this driver as third argument to
		 * return the temperature.
		 */
		info->sensor_device = pdev->dev.parent;
	} else {
		indio_dev->num_channels =
			ARRAY_SIZE(sun4i_gpadc_channels_no_temp);
		indio_dev->channels = sun4i_gpadc_channels_no_temp;
	}

	if (IS_ENABLED(CONFIG_THERMAL_OF)) {
		ret = sun4i_irq_init(pdev, "TEMP_DATA_PENDING",
				     sun4i_gpadc_temp_data_irq_handler,
				     "temp_data", &info->temp_data_irq,
				     &info->ignore_temp_data_irq);
		if (ret < 0)
			return ret;
	}

	ret = sun4i_irq_init(pdev, "FIFO_DATA_PENDING",
			     sun4i_gpadc_fifo_data_irq_handler, "fifo_data",
			     &info->fifo_data_irq, &info->ignore_fifo_data_irq);
	if (ret < 0)
		return ret;

	if (IS_ENABLED(CONFIG_THERMAL_OF)) {
		ret = iio_map_array_register(indio_dev, sun4i_gpadc_hwmon_maps);
		if (ret < 0) {
			dev_err(&pdev->dev,
				"failed to register iio map array\n");
			return ret;
		}
	}

	return 0;
}