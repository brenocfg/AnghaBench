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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mlxreg_fan {struct device* cdev; int /*<<< orphan*/  regmap; struct device* dev; } ;
struct mlxreg_core_platform_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_THERMAL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 scalar_t__ IS_REACHABLE (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct mlxreg_core_platform_data* dev_get_platdata (struct device*) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,char*,struct mlxreg_fan*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlxreg_fan* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device* devm_thermal_of_cooling_device_register (struct device*,int /*<<< orphan*/ *,char*,struct mlxreg_fan*,int /*<<< orphan*/ *) ; 
 int mlxreg_fan_config (struct mlxreg_fan*,struct mlxreg_core_platform_data*) ; 
 int /*<<< orphan*/  mlxreg_fan_cooling_ops ; 
 int /*<<< orphan*/  mlxreg_fan_hwmon_chip_info ; 

__attribute__((used)) static int mlxreg_fan_probe(struct platform_device *pdev)
{
	struct mlxreg_core_platform_data *pdata;
	struct device *dev = &pdev->dev;
	struct mlxreg_fan *fan;
	struct device *hwm;
	int err;

	pdata = dev_get_platdata(dev);
	if (!pdata) {
		dev_err(dev, "Failed to get platform data.\n");
		return -EINVAL;
	}

	fan = devm_kzalloc(dev, sizeof(*fan), GFP_KERNEL);
	if (!fan)
		return -ENOMEM;

	fan->dev = dev;
	fan->regmap = pdata->regmap;

	err = mlxreg_fan_config(fan, pdata);
	if (err)
		return err;

	hwm = devm_hwmon_device_register_with_info(dev, "mlxreg_fan",
						   fan,
						   &mlxreg_fan_hwmon_chip_info,
						   NULL);
	if (IS_ERR(hwm)) {
		dev_err(dev, "Failed to register hwmon device\n");
		return PTR_ERR(hwm);
	}

	if (IS_REACHABLE(CONFIG_THERMAL)) {
		fan->cdev = devm_thermal_of_cooling_device_register(dev,
			NULL, "mlxreg_fan", fan, &mlxreg_fan_cooling_ops);
		if (IS_ERR(fan->cdev)) {
			dev_err(dev, "Failed to register cooling device\n");
			return PTR_ERR(fan->cdev);
		}
	}

	return 0;
}