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
struct resource {int /*<<< orphan*/  parent; } ;
struct device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct device* acpi_get_first_physical_node (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  pci_find_resource (int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static void acpi_platform_fill_resource(struct acpi_device *adev,
	const struct resource *src, struct resource *dest)
{
	struct device *parent;

	*dest = *src;

	/*
	 * If the device has parent we need to take its resources into
	 * account as well because this device might consume part of those.
	 */
	parent = acpi_get_first_physical_node(adev->parent);
	if (parent && dev_is_pci(parent))
		dest->parent = pci_find_resource(to_pci_dev(parent), dest);
}