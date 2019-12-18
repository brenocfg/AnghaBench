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
 int PCI_ACS_CR ; 
 int PCI_ACS_RR ; 
 int PCI_ACS_SV ; 
 int PCI_ACS_UF ; 

__attribute__((used)) static int pci_quirk_brcm_acs(struct pci_dev *dev, u16 acs_flags)
{
	/*
	 * iProc PAXB Root Ports don't advertise an ACS capability, but
	 * they do not allow peer-to-peer transactions between Root Ports.
	 * Allow each Root Port to be in a separate IOMMU group by masking
	 * SV/RR/CR/UF bits.
	 */
	acs_flags &= ~(PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF);

	return acs_flags ? 0 : 1;
}