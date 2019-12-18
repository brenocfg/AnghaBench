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
struct pci_driver {int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_pci_probe ; 
 int /*<<< orphan*/  mlxsw_pci_remove ; 
 int pci_register_driver (struct pci_driver*) ; 

int mlxsw_pci_driver_register(struct pci_driver *pci_driver)
{
	pci_driver->probe = mlxsw_pci_probe;
	pci_driver->remove = mlxsw_pci_remove;
	return pci_register_driver(pci_driver);
}