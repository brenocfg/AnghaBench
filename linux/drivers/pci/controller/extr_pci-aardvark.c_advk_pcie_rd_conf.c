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
typedef  int u32 ;
struct pci_bus {scalar_t__ number; scalar_t__ primary; struct advk_pcie* sysdata; } ;
struct advk_pcie {scalar_t__ root_bus_nr; int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SET_FAILED ; 
 int PCIBIOS_SUCCESSFUL ; 
 int PCIE_CONFIG_RD_TYPE0 ; 
 int PCIE_CONFIG_RD_TYPE1 ; 
 int PCIE_CONF_ADDR (scalar_t__,int,int) ; 
 int /*<<< orphan*/  PIO_ADDR_LS ; 
 int /*<<< orphan*/  PIO_ADDR_MS ; 
 int /*<<< orphan*/  PIO_CTRL ; 
 int PIO_CTRL_TYPE_MASK ; 
 int /*<<< orphan*/  PIO_ISR ; 
 int /*<<< orphan*/  PIO_RD_DATA ; 
 int /*<<< orphan*/  PIO_START ; 
 int /*<<< orphan*/  PIO_WR_DATA_STRB ; 
 int /*<<< orphan*/  advk_pcie_check_pio_status (struct advk_pcie*) ; 
 int /*<<< orphan*/  advk_pcie_valid_device (struct advk_pcie*,struct pci_bus*,int) ; 
 int advk_pcie_wait_pio (struct advk_pcie*) ; 
 int advk_readl (struct advk_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advk_writel (struct advk_pcie*,int,int /*<<< orphan*/ ) ; 
 int pci_bridge_emul_conf_read (int /*<<< orphan*/ *,int,int,int*) ; 

__attribute__((used)) static int advk_pcie_rd_conf(struct pci_bus *bus, u32 devfn,
			     int where, int size, u32 *val)
{
	struct advk_pcie *pcie = bus->sysdata;
	u32 reg;
	int ret;

	if (!advk_pcie_valid_device(pcie, bus, devfn)) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	if (bus->number == pcie->root_bus_nr)
		return pci_bridge_emul_conf_read(&pcie->bridge, where,
						 size, val);

	/* Start PIO */
	advk_writel(pcie, 0, PIO_START);
	advk_writel(pcie, 1, PIO_ISR);

	/* Program the control register */
	reg = advk_readl(pcie, PIO_CTRL);
	reg &= ~PIO_CTRL_TYPE_MASK;
	if (bus->primary ==  pcie->root_bus_nr)
		reg |= PCIE_CONFIG_RD_TYPE0;
	else
		reg |= PCIE_CONFIG_RD_TYPE1;
	advk_writel(pcie, reg, PIO_CTRL);

	/* Program the address registers */
	reg = PCIE_CONF_ADDR(bus->number, devfn, where);
	advk_writel(pcie, reg, PIO_ADDR_LS);
	advk_writel(pcie, 0, PIO_ADDR_MS);

	/* Program the data strobe */
	advk_writel(pcie, 0xf, PIO_WR_DATA_STRB);

	/* Start the transfer */
	advk_writel(pcie, 1, PIO_START);

	ret = advk_pcie_wait_pio(pcie);
	if (ret < 0)
		return PCIBIOS_SET_FAILED;

	advk_pcie_check_pio_status(pcie);

	/* Get the read result */
	*val = advk_readl(pcie, PIO_RD_DATA);
	if (size == 1)
		*val = (*val >> (8 * (where & 3))) & 0xff;
	else if (size == 2)
		*val = (*val >> (8 * (where & 3))) & 0xffff;

	return PCIBIOS_SUCCESSFUL;
}