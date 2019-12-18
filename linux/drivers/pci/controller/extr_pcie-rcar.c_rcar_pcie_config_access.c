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
typedef  int u32 ;
struct rcar_pcie {int root_bus_nr; } ;
struct pci_bus {TYPE_1__* parent; int /*<<< orphan*/  number; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int CONFIG_SEND_ENABLE ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCICONF (unsigned int) ; 
 int /*<<< orphan*/  PCIECAR ; 
 int /*<<< orphan*/  PCIECCTLR ; 
 int /*<<< orphan*/  PCIECDR ; 
 int /*<<< orphan*/  PCIEERRFR ; 
 unsigned int PCIE_CONF_BUS (int /*<<< orphan*/ ) ; 
 unsigned int PCIE_CONF_DEV (unsigned int) ; 
 unsigned int PCIE_CONF_FUNC (unsigned int) ; 
 unsigned int PCI_FUNC (unsigned int) ; 
 unsigned int PCI_PRIMARY_BUS ; 
 unsigned int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_REC_MASTER_ABORT ; 
 int PCI_STATUS_REC_TARGET_ABORT ; 
 unsigned char RCAR_PCI_ACCESS_READ ; 
 int /*<<< orphan*/  RCONF (int /*<<< orphan*/ ) ; 
 int TYPE0 ; 
 int TYPE1 ; 
 int UNSUPPORTED_REQUEST ; 
 scalar_t__ pci_is_root_bus (struct pci_bus*) ; 
 int rcar_pci_read_reg (struct rcar_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int,int /*<<< orphan*/ ) ; 
 int rcar_read_conf (struct rcar_pcie*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_pcie_config_access(struct rcar_pcie *pcie,
		unsigned char access_type, struct pci_bus *bus,
		unsigned int devfn, int where, u32 *data)
{
	unsigned int dev, func, reg, index;

	dev = PCI_SLOT(devfn);
	func = PCI_FUNC(devfn);
	reg = where & ~3;
	index = reg / 4;

	/*
	 * While each channel has its own memory-mapped extended config
	 * space, it's generally only accessible when in endpoint mode.
	 * When in root complex mode, the controller is unable to target
	 * itself with either type 0 or type 1 accesses, and indeed, any
	 * controller initiated target transfer to its own config space
	 * result in a completer abort.
	 *
	 * Each channel effectively only supports a single device, but as
	 * the same channel <-> device access works for any PCI_SLOT()
	 * value, we cheat a bit here and bind the controller's config
	 * space to devfn 0 in order to enable self-enumeration. In this
	 * case the regular ECAR/ECDR path is sidelined and the mangled
	 * config access itself is initiated as an internal bus transaction.
	 */
	if (pci_is_root_bus(bus)) {
		if (dev != 0)
			return PCIBIOS_DEVICE_NOT_FOUND;

		if (access_type == RCAR_PCI_ACCESS_READ) {
			*data = rcar_pci_read_reg(pcie, PCICONF(index));
		} else {
			/* Keep an eye out for changes to the root bus number */
			if (pci_is_root_bus(bus) && (reg == PCI_PRIMARY_BUS))
				pcie->root_bus_nr = *data & 0xff;

			rcar_pci_write_reg(pcie, *data, PCICONF(index));
		}

		return PCIBIOS_SUCCESSFUL;
	}

	if (pcie->root_bus_nr < 0)
		return PCIBIOS_DEVICE_NOT_FOUND;

	/* Clear errors */
	rcar_pci_write_reg(pcie, rcar_pci_read_reg(pcie, PCIEERRFR), PCIEERRFR);

	/* Set the PIO address */
	rcar_pci_write_reg(pcie, PCIE_CONF_BUS(bus->number) |
		PCIE_CONF_DEV(dev) | PCIE_CONF_FUNC(func) | reg, PCIECAR);

	/* Enable the configuration access */
	if (bus->parent->number == pcie->root_bus_nr)
		rcar_pci_write_reg(pcie, CONFIG_SEND_ENABLE | TYPE0, PCIECCTLR);
	else
		rcar_pci_write_reg(pcie, CONFIG_SEND_ENABLE | TYPE1, PCIECCTLR);

	/* Check for errors */
	if (rcar_pci_read_reg(pcie, PCIEERRFR) & UNSUPPORTED_REQUEST)
		return PCIBIOS_DEVICE_NOT_FOUND;

	/* Check for master and target aborts */
	if (rcar_read_conf(pcie, RCONF(PCI_STATUS)) &
		(PCI_STATUS_REC_MASTER_ABORT | PCI_STATUS_REC_TARGET_ABORT))
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (access_type == RCAR_PCI_ACCESS_READ)
		*data = rcar_pci_read_reg(pcie, PCIECDR);
	else
		rcar_pci_write_reg(pcie, *data, PCIECDR);

	/* Disable the configuration access */
	rcar_pci_write_reg(pcie, 0, PCIECCTLR);

	return PCIBIOS_SUCCESSFUL;
}