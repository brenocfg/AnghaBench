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
struct nvdimm_bus_descriptor {int /*<<< orphan*/  provider_name; } ;
struct acpi_nfit_desc {int /*<<< orphan*/  dev; struct nvdimm_bus_descriptor nd_desc; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct acpi_device* to_acpi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct acpi_device *to_acpi_dev(struct acpi_nfit_desc *acpi_desc)
{
	struct nvdimm_bus_descriptor *nd_desc = &acpi_desc->nd_desc;

	/*
	 * If provider == 'ACPI.NFIT' we can assume 'dev' is a struct
	 * acpi_device.
	 */
	if (!nd_desc->provider_name
			|| strcmp(nd_desc->provider_name, "ACPI.NFIT") != 0)
		return NULL;

	return to_acpi_device(acpi_desc->dev);
}