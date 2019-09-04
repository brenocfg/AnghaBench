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
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 scalar_t__ PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_NLW ; 
 unsigned int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static unsigned pcie_link_get_lanes(struct cobalt *cobalt)
{
	struct pci_dev *pci_dev = cobalt->pci_dev;
	unsigned offset;
	u16 link;

	offset = pci_find_capability(pci_dev, PCI_CAP_ID_EXP);
	if (!offset)
		return 0;
	pci_read_config_word(pci_dev, offset + PCI_EXP_LNKSTA, &link);
	return (link & PCI_EXP_LNKSTA_NLW) >> 4;
}