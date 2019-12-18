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
 int /*<<< orphan*/  pci_quirk_cavium_acs_match (struct pci_dev*) ; 

__attribute__((used)) static int pci_quirk_cavium_acs(struct pci_dev *dev, u16 acs_flags)
{
	/*
	 * Cavium root ports don't advertise an ACS capability.  However,
	 * the RTL internally implements similar protection as if ACS had
	 * Request Redirection, Completion Redirection, Source Validation,
	 * and Upstream Forwarding features enabled.  Assert that the
	 * hardware implements and enables equivalent ACS functionality for
	 * these flags.
	 */
	acs_flags &= ~(PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_SV | PCI_ACS_UF);

	if (!pci_quirk_cavium_acs_match(dev))
		return -ENOTTY;

	return acs_flags ? 0 : 1;
}