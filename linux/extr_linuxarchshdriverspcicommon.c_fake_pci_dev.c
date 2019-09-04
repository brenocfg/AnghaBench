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
struct pci_dev {int devfn; struct pci_channel* sysdata; struct pci_bus* bus; } ;
struct pci_channel {int /*<<< orphan*/  pci_ops; } ;
struct pci_bus {int number; struct pci_bus* parent; int /*<<< orphan*/  ops; struct pci_channel* sysdata; } ;

/* Variables and functions */

__attribute__((used)) static struct pci_dev *fake_pci_dev(struct pci_channel *hose,
	int top_bus, int busnr, int devfn)
{
	static struct pci_dev dev;
	static struct pci_bus bus;

	dev.bus = &bus;
	dev.sysdata = hose;
	dev.devfn = devfn;
	bus.number = busnr;
	bus.sysdata = hose;
	bus.ops = hose->pci_ops;

	if(busnr != top_bus)
		/* Fake a parent bus structure. */
		bus.parent = &bus;
	else
		bus.parent = NULL;

	return &dev;
}