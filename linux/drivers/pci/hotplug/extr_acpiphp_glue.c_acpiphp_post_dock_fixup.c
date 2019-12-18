#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int start; scalar_t__ end; } ;
struct pci_bus {int /*<<< orphan*/  self; TYPE_3__ busn_res; scalar_t__ primary; } ;
struct TYPE_5__ {TYPE_1__* slot; } ;
struct acpiphp_context {TYPE_2__ func; } ;
struct acpi_device {int dummy; } ;
struct TYPE_4__ {struct pci_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_PRIMARY_BUS ; 
 struct acpiphp_context* acpiphp_grab_context (struct acpi_device*) ; 
 int /*<<< orphan*/  acpiphp_let_context_go (struct acpiphp_context*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void acpiphp_post_dock_fixup(struct acpi_device *adev)
{
	struct acpiphp_context *context = acpiphp_grab_context(adev);
	struct pci_bus *bus;
	u32 buses;

	if (!context)
		return;

	bus = context->func.slot->bus;
	if (!bus->self)
		goto out;

	/* fixup bad _DCK function that rewrites
	 * secondary bridge on slot
	 */
	pci_read_config_dword(bus->self, PCI_PRIMARY_BUS, &buses);

	if (((buses >> 8) & 0xff) != bus->busn_res.start) {
		buses = (buses & 0xff000000)
			| ((unsigned int)(bus->primary)     <<  0)
			| ((unsigned int)(bus->busn_res.start)   <<  8)
			| ((unsigned int)(bus->busn_res.end) << 16);
		pci_write_config_dword(bus->self, PCI_PRIMARY_BUS, buses);
	}

 out:
	acpiphp_let_context_go(context);
}