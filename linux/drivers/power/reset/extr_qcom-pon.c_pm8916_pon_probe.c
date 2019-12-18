#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  write; TYPE_1__* dev; } ;
struct pm8916_pon {long reason_shift; TYPE_3__ reboot_mode; int /*<<< orphan*/  baseaddr; int /*<<< orphan*/  regmap; TYPE_1__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pm8916_pon* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (TYPE_1__*) ; 
 int devm_reboot_mode_register (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct pm8916_pon*) ; 
 int /*<<< orphan*/  pm8916_reboot_mode_write ; 

__attribute__((used)) static int pm8916_pon_probe(struct platform_device *pdev)
{
	struct pm8916_pon *pon;
	int error;

	pon = devm_kzalloc(&pdev->dev, sizeof(*pon), GFP_KERNEL);
	if (!pon)
		return -ENOMEM;

	pon->dev = &pdev->dev;

	pon->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!pon->regmap) {
		dev_err(&pdev->dev, "failed to locate regmap\n");
		return -ENODEV;
	}

	error = of_property_read_u32(pdev->dev.of_node, "reg",
				     &pon->baseaddr);
	if (error)
		return error;

	pon->reboot_mode.dev = &pdev->dev;
	pon->reason_shift = (long)of_device_get_match_data(&pdev->dev);
	pon->reboot_mode.write = pm8916_reboot_mode_write;
	error = devm_reboot_mode_register(&pdev->dev, &pon->reboot_mode);
	if (error) {
		dev_err(&pdev->dev, "can't register reboot mode\n");
		return error;
	}

	platform_set_drvdata(pdev, pon);

	return devm_of_platform_populate(&pdev->dev);
}