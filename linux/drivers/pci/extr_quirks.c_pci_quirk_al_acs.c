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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
 int PCI_ACS_CR ; 
 int PCI_ACS_RR ; 
 int PCI_ACS_SV ; 
 int PCI_ACS_UF ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 

__attribute__((used)) static int pci_quirk_al_acs(struct pci_dev *dev, u16 acs_flags)
{
	if (pci_pcie_type(dev) != PCI_EXP_TYPE_ROOT_PORT)
		return -ENOTTY;

	/*
	 * Amazon's Annapurna Labs root ports don't include an ACS capability,
	 * but do include ACS-like functionality. The hardware doesn't support
	 * peer-to-peer transactions via the root port and each has a unique
	 * segment number.
	 *
	 * Additionally, the root ports cannot send traffic to each other.
	 */
	acs_flags &= ~(PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);

	return acs_flags ? 0 : 1;
}