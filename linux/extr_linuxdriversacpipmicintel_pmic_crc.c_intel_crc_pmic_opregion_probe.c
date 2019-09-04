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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct intel_soc_pmic {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 struct intel_soc_pmic* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_crc_pmic_opregion_data ; 
 int intel_pmic_install_opregion_handler (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_crc_pmic_opregion_probe(struct platform_device *pdev)
{
	struct intel_soc_pmic *pmic = dev_get_drvdata(pdev->dev.parent);
	return intel_pmic_install_opregion_handler(&pdev->dev,
			ACPI_HANDLE(pdev->dev.parent), pmic->regmap,
			&intel_crc_pmic_opregion_data);
}