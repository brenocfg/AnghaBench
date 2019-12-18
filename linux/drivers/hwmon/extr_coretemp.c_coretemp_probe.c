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
struct platform_device {int /*<<< orphan*/  id; struct device dev; } ;
struct platform_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  pkg_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct platform_data*,int /*<<< orphan*/ *) ; 
 struct platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct platform_data*) ; 

__attribute__((used)) static int coretemp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct platform_data *pdata;

	/* Initialize the per-zone data structures */
	pdata = devm_kzalloc(dev, sizeof(struct platform_data), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	pdata->pkg_id = pdev->id;
	platform_set_drvdata(pdev, pdata);

	pdata->hwmon_dev = devm_hwmon_device_register_with_groups(dev, DRVNAME,
								  pdata, NULL);
	return PTR_ERR_OR_ZERO(pdata->hwmon_dev);
}