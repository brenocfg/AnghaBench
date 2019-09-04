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
struct pci_pbm_info {int /*<<< orphan*/  devhandle; } ;
struct pci_bus {unsigned int number; struct pci_pbm_info* sysdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_PCI_DEVICE_BUILD (unsigned int,unsigned int,unsigned int) ; 
 int PCIBIOS_SUCCESSFUL ; 
 unsigned int PCI_FUNC (unsigned int) ; 
 unsigned int PCI_SLOT (unsigned int) ; 
 scalar_t__ config_out_of_range (struct pci_pbm_info*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  pci_sun4v_config_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4v_write_pci_cfg(struct pci_bus *bus_dev, unsigned int devfn,
			       int where, int size, u32 value)
{
	struct pci_pbm_info *pbm = bus_dev->sysdata;
	u32 devhandle = pbm->devhandle;
	unsigned int bus = bus_dev->number;
	unsigned int device = PCI_SLOT(devfn);
	unsigned int func = PCI_FUNC(devfn);

	if (config_out_of_range(pbm, bus, devfn, where)) {
		/* Do nothing. */
	} else {
		/* We don't check for hypervisor errors here, but perhaps
		 * we should and influence our return value depending upon
		 * what kind of error is thrown.
		 */
		pci_sun4v_config_put(devhandle,
				     HV_PCI_DEVICE_BUILD(bus, device, func),
				     where, size, value);
	}
	return PCIBIOS_SUCCESSFUL;
}