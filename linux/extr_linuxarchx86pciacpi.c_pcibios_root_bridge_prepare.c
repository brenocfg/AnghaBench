#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_sysdata {int /*<<< orphan*/  companion; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct pci_host_bridge {TYPE_2__ dev; TYPE_1__* bus; } ;
struct TYPE_3__ {struct pci_sysdata* sysdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 

int pcibios_root_bridge_prepare(struct pci_host_bridge *bridge)
{
	/*
	 * We pass NULL as parent to pci_create_root_bus(), so if it is not NULL
	 * here, pci_create_root_bus() has been called by someone else and
	 * sysdata is likely to be different from what we expect.  Let it go in
	 * that case.
	 */
	if (!bridge->dev.parent) {
		struct pci_sysdata *sd = bridge->bus->sysdata;
		ACPI_COMPANION_SET(&bridge->dev, sd->companion);
	}
	return 0;
}