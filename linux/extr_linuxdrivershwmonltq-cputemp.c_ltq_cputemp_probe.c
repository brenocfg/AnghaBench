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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 scalar_t__ SOC_TYPE_VR9_2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_add_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct device* devm_hwmon_device_register_with_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltq_chip_info ; 
 int /*<<< orphan*/  ltq_cputemp_disable ; 
 int /*<<< orphan*/  ltq_cputemp_enable () ; 
 scalar_t__ ltq_soc_type () ; 

__attribute__((used)) static int ltq_cputemp_probe(struct platform_device *pdev)
{
	struct device *hwmon_dev;
	int err = 0;

	/* available on vr9 v1.2 SoCs only */
	if (ltq_soc_type() != SOC_TYPE_VR9_2)
		return -ENODEV;

	err = devm_add_action(&pdev->dev, ltq_cputemp_disable, NULL);
	if (err)
		return err;

	ltq_cputemp_enable();

	hwmon_dev = devm_hwmon_device_register_with_info(&pdev->dev,
							 "ltq_cputemp",
							 NULL,
							 &ltq_chip_info,
							 NULL);

	if (IS_ERR(hwmon_dev)) {
		dev_err(&pdev->dev, "Failed to register as hwmon device");
		return PTR_ERR(hwmon_dev);
	}

	return 0;
}