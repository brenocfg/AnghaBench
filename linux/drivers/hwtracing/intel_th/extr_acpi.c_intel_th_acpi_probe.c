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
struct resource {int flags; } ;
struct platform_device {int num_resources; int /*<<< orphan*/  dev; struct resource* resource; } ;
struct intel_th {int dummy; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct acpi_device {struct intel_th* driver_data; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int IORESOURCE_IRQ ; 
 int IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct intel_th*) ; 
 int PTR_ERR (struct intel_th*) ; 
 int TH_MMIO_END ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_th_acpi_ids ; 
 struct intel_th* intel_th_alloc (int /*<<< orphan*/ *,void*,struct resource*,int) ; 

__attribute__((used)) static int intel_th_acpi_probe(struct platform_device *pdev)
{
	struct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	struct resource resource[TH_MMIO_END];
	const struct acpi_device_id *id;
	struct intel_th *th;
	int i, r;

	id = acpi_match_device(intel_th_acpi_ids, &pdev->dev);
	if (!id)
		return -ENODEV;

	for (i = 0, r = 0; i < pdev->num_resources && r < TH_MMIO_END; i++)
		if (pdev->resource[i].flags &
		    (IORESOURCE_IRQ | IORESOURCE_MEM))
			resource[r++] = pdev->resource[i];

	th = intel_th_alloc(&pdev->dev, (void *)id->driver_data, resource, r);
	if (IS_ERR(th))
		return PTR_ERR(th);

	adev->driver_data = th;

	return 0;
}