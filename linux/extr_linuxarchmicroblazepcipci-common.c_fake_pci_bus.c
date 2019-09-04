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
struct pci_controller {int /*<<< orphan*/ * ops; } ;
struct pci_bus {int number; int /*<<< orphan*/ * ops; struct pci_controller* sysdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  null_pci_ops ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static struct pci_bus *
fake_pci_bus(struct pci_controller *hose, int busnr)
{
	static struct pci_bus bus;

	if (!hose)
		pr_err("Can't find hose for PCI bus %d!\n", busnr);

	bus.number = busnr;
	bus.sysdata = hose;
	bus.ops = hose ? hose->ops : &null_pci_ops;
	return &bus;
}