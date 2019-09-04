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
struct platform_device {int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; int /*<<< orphan*/  dev; } ;
struct intel_th {int dummy; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct acpi_device {struct intel_th* driver_data; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct intel_th*) ; 
 int PTR_ERR (struct intel_th*) ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_th_acpi_ids ; 
 struct intel_th* intel_th_alloc (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int intel_th_acpi_probe(struct platform_device *pdev)
{
	struct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	const struct acpi_device_id *id;
	struct intel_th *th;

	id = acpi_match_device(intel_th_acpi_ids, &pdev->dev);
	if (!id)
		return -ENODEV;

	th = intel_th_alloc(&pdev->dev, (void *)id->driver_data,
			    pdev->resource, pdev->num_resources, -1);
	if (IS_ERR(th))
		return PTR_ERR(th);

	adev->driver_data = th;

	return 0;
}