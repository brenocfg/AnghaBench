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
struct vexpress_hwmon_type {int /*<<< orphan*/  attr_groups; int /*<<< orphan*/  name; } ;
struct vexpress_hwmon_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  reg; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {struct vexpress_hwmon_type* data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vexpress_hwmon_data*,int /*<<< orphan*/ ) ; 
 struct vexpress_hwmon_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_vexpress_config (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vexpress_hwmon_data*) ; 
 int /*<<< orphan*/  vexpress_hwmon_of_match ; 

__attribute__((used)) static int vexpress_hwmon_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct vexpress_hwmon_data *data;
	const struct vexpress_hwmon_type *type;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	platform_set_drvdata(pdev, data);

	match = of_match_device(vexpress_hwmon_of_match, &pdev->dev);
	if (!match)
		return -ENODEV;
	type = match->data;

	data->reg = devm_regmap_init_vexpress_config(&pdev->dev);
	if (IS_ERR(data->reg))
		return PTR_ERR(data->reg);

	data->hwmon_dev = devm_hwmon_device_register_with_groups(&pdev->dev,
			type->name, data, type->attr_groups);

	return PTR_ERR_OR_ZERO(data->hwmon_dev);
}