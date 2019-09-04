#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct device* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct axp20x_dev {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ADR_SPACE_GPIO ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_install_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axp20x_dev* dev_get_drvdata (struct device*) ; 
 int intel_pmic_install_opregion_handler (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_xpower_pmic_gpio_handler ; 
 int /*<<< orphan*/  intel_xpower_pmic_opregion_data ; 

__attribute__((used)) static int intel_xpower_pmic_opregion_probe(struct platform_device *pdev)
{
	struct device *parent = pdev->dev.parent;
	struct axp20x_dev *axp20x = dev_get_drvdata(parent);
	acpi_status status;
	int result;

	status = acpi_install_address_space_handler(ACPI_HANDLE(parent),
			ACPI_ADR_SPACE_GPIO, intel_xpower_pmic_gpio_handler,
			NULL, NULL);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	result = intel_pmic_install_opregion_handler(&pdev->dev,
					ACPI_HANDLE(parent), axp20x->regmap,
					&intel_xpower_pmic_opregion_data);
	if (result)
		acpi_remove_address_space_handler(ACPI_HANDLE(parent),
						  ACPI_ADR_SPACE_GPIO,
						  intel_xpower_pmic_gpio_handler);

	return result;
}