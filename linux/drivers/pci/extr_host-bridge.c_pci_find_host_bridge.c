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
struct pci_host_bridge {int dummy; } ;
struct pci_bus {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 struct pci_bus* find_pci_root_bus (struct pci_bus*) ; 
 struct pci_host_bridge* to_pci_host_bridge (int /*<<< orphan*/ ) ; 

struct pci_host_bridge *pci_find_host_bridge(struct pci_bus *bus)
{
	struct pci_bus *root_bus = find_pci_root_bus(bus);

	return to_pci_host_bridge(root_bus->bridge);
}