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
struct intel_lpss_platform_info {int /*<<< orphan*/  irq; int /*<<< orphan*/  mem; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct intel_lpss_platform_info* devm_kmemdup (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_lpss_acpi_ids ; 
 int intel_lpss_probe (int /*<<< orphan*/ *,struct intel_lpss_platform_info*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_lpss_acpi_probe(struct platform_device *pdev)
{
	struct intel_lpss_platform_info *info;
	const struct acpi_device_id *id;

	id = acpi_match_device(intel_lpss_acpi_ids, &pdev->dev);
	if (!id)
		return -ENODEV;

	info = devm_kmemdup(&pdev->dev, (void *)id->driver_data, sizeof(*info),
			    GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	info->irq = platform_get_irq(pdev, 0);

	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	return intel_lpss_probe(&pdev->dev, info);
}