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
struct cobalt {struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_NLW ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned pcie_link_get_lanes(struct cobalt *cobalt)
{
	struct pci_dev *pci_dev = cobalt->pci_dev;
	u16 link;

	if (!pci_is_pcie(pci_dev))
		return 0;
	pcie_capability_read_word(pci_dev, PCI_EXP_LNKSTA, &link);
	return (link & PCI_EXP_LNKSTA_NLW) >> 4;
}