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
struct kset {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kset* bus_get_kset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  pci_slots_kset ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int pci_slot_init(void)
{
	struct kset *pci_bus_kset;

	pci_bus_kset = bus_get_kset(&pci_bus_type);
	pci_slots_kset = kset_create_and_add("slots", NULL,
						&pci_bus_kset->kobj);
	if (!pci_slots_kset) {
		pr_err("PCI: Slot initialization failure\n");
		return -ENOMEM;
	}
	return 0;
}