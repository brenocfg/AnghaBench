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
typedef  int /*<<< orphan*/  u32 ;
struct pci_ops {int (* read ) (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ *) ;} ;
struct pci_bus {struct pci_ops* ops; } ;

/* Variables and functions */
 struct pci_ops* __find_pci_bus_ops (struct pci_bus*) ; 
 int stub1 (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aer_inj_read(struct pci_bus *bus, unsigned int devfn, int where,
			int size, u32 *val)
{
	struct pci_ops *ops, *my_ops;
	int rv;

	ops = __find_pci_bus_ops(bus);
	if (!ops)
		return -1;

	my_ops = bus->ops;
	bus->ops = ops;
	rv = ops->read(bus, devfn, where, size, val);
	bus->ops = my_ops;

	return rv;
}