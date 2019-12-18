#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rpi_hwmon_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  get_values_poll_work; int /*<<< orphan*/  fw; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_hwmon_device_register_with_info (struct device*,char*,struct rpi_hwmon_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rpi_hwmon_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_values_poll ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rpi_hwmon_data*) ; 
 int /*<<< orphan*/  rpi_chip_info ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rpi_hwmon_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rpi_hwmon_data *data;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	/* Parent driver assure that firmware is correct */
	data->fw = dev_get_drvdata(dev->parent);

	data->hwmon_dev = devm_hwmon_device_register_with_info(dev, "rpi_volt",
							       data,
							       &rpi_chip_info,
							       NULL);

	INIT_DELAYED_WORK(&data->get_values_poll_work, get_values_poll);
	platform_set_drvdata(pdev, data);

	if (!PTR_ERR_OR_ZERO(data->hwmon_dev))
		schedule_delayed_work(&data->get_values_poll_work, 2 * HZ);

	return PTR_ERR_OR_ZERO(data->hwmon_dev);
}