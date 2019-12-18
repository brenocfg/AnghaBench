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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_wakeup ; 
 int /*<<< orphan*/  pci_walk_bus (struct pci_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void pci_wakeup_bus(struct pci_bus *bus)
{
	if (bus)
		pci_walk_bus(bus, pci_wakeup, NULL);
}