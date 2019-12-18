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
struct pci_dev {int dummy; } ;
typedef  enum pci_bus_speed { ____Placeholder_pci_bus_speed } pci_bus_speed ;

/* Variables and functions */
 int PCIE_SPEED_16_0GT ; 
 int PCIE_SPEED_2_5GT ; 
 int PCIE_SPEED_32_0GT ; 
 int PCIE_SPEED_5_0GT ; 
 int PCIE_SPEED_8_0GT ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP2 ; 
 int PCI_EXP_LNKCAP2_SLS_16_0GB ; 
 int PCI_EXP_LNKCAP2_SLS_2_5GB ; 
 int PCI_EXP_LNKCAP2_SLS_32_0GB ; 
 int PCI_EXP_LNKCAP2_SLS_5_0GB ; 
 int PCI_EXP_LNKCAP2_SLS_8_0GB ; 
 int PCI_EXP_LNKCAP_SLS ; 
 int PCI_EXP_LNKCAP_SLS_2_5GB ; 
 int PCI_EXP_LNKCAP_SLS_5_0GB ; 
 int PCI_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

enum pci_bus_speed pcie_get_speed_cap(struct pci_dev *dev)
{
	u32 lnkcap2, lnkcap;

	/*
	 * Link Capabilities 2 was added in PCIe r3.0, sec 7.8.18.  The
	 * implementation note there recommends using the Supported Link
	 * Speeds Vector in Link Capabilities 2 when supported.
	 *
	 * Without Link Capabilities 2, i.e., prior to PCIe r3.0, software
	 * should use the Supported Link Speeds field in Link Capabilities,
	 * where only 2.5 GT/s and 5.0 GT/s speeds were defined.
	 */
	pcie_capability_read_dword(dev, PCI_EXP_LNKCAP2, &lnkcap2);
	if (lnkcap2) { /* PCIe r3.0-compliant */
		if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_32_0GB)
			return PCIE_SPEED_32_0GT;
		else if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_16_0GB)
			return PCIE_SPEED_16_0GT;
		else if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_8_0GB)
			return PCIE_SPEED_8_0GT;
		else if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_5_0GB)
			return PCIE_SPEED_5_0GT;
		else if (lnkcap2 & PCI_EXP_LNKCAP2_SLS_2_5GB)
			return PCIE_SPEED_2_5GT;
		return PCI_SPEED_UNKNOWN;
	}

	pcie_capability_read_dword(dev, PCI_EXP_LNKCAP, &lnkcap);
	if ((lnkcap & PCI_EXP_LNKCAP_SLS) == PCI_EXP_LNKCAP_SLS_5_0GB)
		return PCIE_SPEED_5_0GT;
	else if ((lnkcap & PCI_EXP_LNKCAP_SLS) == PCI_EXP_LNKCAP_SLS_2_5GB)
		return PCIE_SPEED_2_5GT;

	return PCI_SPEED_UNKNOWN;
}