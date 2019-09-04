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
struct pci_controller {scalar_t__ io_base_phys; scalar_t__ pci_mem_offset; scalar_t__ first_busno; } ;

/* Variables and functions */
 long ENODEV ; 
 long EOPNOTSUPP ; 
#define  IOBASE_BRIDGE_NUMBER 132 
#define  IOBASE_IO 131 
#define  IOBASE_ISA_IO 130 
#define  IOBASE_ISA_MEM 129 
#define  IOBASE_MEMORY 128 
 scalar_t__ isa_io_base ; 
 scalar_t__ isa_mem_base ; 
 struct pci_controller* pci_bus_to_hose (unsigned long) ; 

long sys_pciconfig_iobase(long which, unsigned long bus, unsigned long devfn)
{
	struct pci_controller *hose;
	long result = -EOPNOTSUPP;

	hose = pci_bus_to_hose(bus);
	if (!hose)
		return -ENODEV;

	switch (which) {
	case IOBASE_BRIDGE_NUMBER:
		return (long)hose->first_busno;
	case IOBASE_MEMORY:
		return (long)hose->pci_mem_offset;
	case IOBASE_IO:
		return (long)hose->io_base_phys;
	case IOBASE_ISA_IO:
		return (long)isa_io_base;
	case IOBASE_ISA_MEM:
		return (long)isa_mem_base;
	}

	return result;
}