#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct cobalt {TYPE_2__* pci_dev; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 scalar_t__ PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_MLW ; 
 unsigned int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 

__attribute__((used)) static unsigned pcie_bus_link_get_lanes(struct cobalt *cobalt)
{
	struct pci_dev *pci_dev = cobalt->pci_dev->bus->self;
	unsigned offset;
	u32 link;

	offset = pci_find_capability(pci_dev, PCI_CAP_ID_EXP);
	if (!offset)
		return 0;
	pci_read_config_dword(pci_dev, offset + PCI_EXP_LNKCAP, &link);
	return (link & PCI_EXP_LNKCAP_MLW) >> 4;
}