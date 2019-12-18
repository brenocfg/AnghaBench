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
struct pci_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct eeepc_laptop {TYPE_1__ hotplug_slot; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  eeepc_hotplug_slot_ops ; 
 struct pci_bus* pci_find_bus (int /*<<< orphan*/ ,int) ; 
 int pci_hp_register (TYPE_1__*,struct pci_bus*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int eeepc_setup_pci_hotplug(struct eeepc_laptop *eeepc)
{
	int ret = -ENOMEM;
	struct pci_bus *bus = pci_find_bus(0, 1);

	if (!bus) {
		pr_err("Unable to find wifi PCI bus\n");
		return -ENODEV;
	}

	eeepc->hotplug_slot.ops = &eeepc_hotplug_slot_ops;

	ret = pci_hp_register(&eeepc->hotplug_slot, bus, 0, "eeepc-wifi");
	if (ret) {
		pr_err("Unable to register hotplug slot - %d\n", ret);
		goto error_register;
	}

	return 0;

error_register:
	eeepc->hotplug_slot.ops = NULL;
	return ret;
}