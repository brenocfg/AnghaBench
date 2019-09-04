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
typedef  int /*<<< orphan*/  u32 ;
struct pci_bus {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* read ) (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 struct pci_bus* pci_find_bus (unsigned int,unsigned int) ; 
 int stub1 (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ *) ; 

int raw_pci_read(unsigned int domain, unsigned int bus,
		  unsigned int devfn, int reg, int len, u32 *val)
{
	struct pci_bus *b = pci_find_bus(domain, bus);

	if (!b)
		return PCIBIOS_DEVICE_NOT_FOUND;
	return b->ops->read(b, devfn, reg, len, val);
}