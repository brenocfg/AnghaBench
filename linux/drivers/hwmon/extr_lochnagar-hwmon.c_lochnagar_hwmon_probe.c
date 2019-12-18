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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct lochnagar_hwmon {int* power_nsamples; int /*<<< orphan*/  regmap; int /*<<< orphan*/  sensor_lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct device* devm_hwmon_device_register_with_info (struct device*,char*,struct lochnagar_hwmon*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct lochnagar_hwmon* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lochnagar_chip_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lochnagar_hwmon_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device *hwmon_dev;
	struct lochnagar_hwmon *priv;
	int i;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->sensor_lock);

	priv->regmap = dev_get_regmap(dev->parent, NULL);
	if (!priv->regmap) {
		dev_err(dev, "No register map found\n");
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(priv->power_nsamples); i++)
		priv->power_nsamples[i] = 96;

	hwmon_dev = devm_hwmon_device_register_with_info(dev, "Lochnagar", priv,
							 &lochnagar_chip_info,
							 NULL);

	return PTR_ERR_OR_ZERO(hwmon_dev);
}