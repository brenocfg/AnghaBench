#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ has_acpi_companion (TYPE_1__*) ; 
 int msm_pinctrl_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdm845_acpi_pinctrl ; 
 int /*<<< orphan*/  sdm845_pinctrl ; 

__attribute__((used)) static int sdm845_pinctrl_probe(struct platform_device *pdev)
{
	int ret;

	if (pdev->dev.of_node) {
		ret = msm_pinctrl_probe(pdev, &sdm845_pinctrl);
	} else if (has_acpi_companion(&pdev->dev)) {
		ret = msm_pinctrl_probe(pdev, &sdm845_acpi_pinctrl);
	} else {
		dev_err(&pdev->dev, "DT and ACPI disabled\n");
		return -EINVAL;
	}

	return ret;
}